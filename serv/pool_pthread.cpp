/* 一个简单的线程池（固定数量线程）
 * 线程池　＝　多个线程　＋　任务队列
 */
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <stdlib.h>
using namespace std;

const int MAX_THREAD=5;
const int MAX_QUEUE=10;

class Task{
public:
    void SetData(int data)
    {
        _data = data;
    }
    bool Run(int size)
    {
        srand(time(NULL));
        int n = rand()%5;
        printf("%p run %d --- %d---sleep:%d\n",(void*)pthread_self(), size,_data, n);
        sleep(n);
        return true;
    }
private:
    int _data;
};

class ThreadPool{
public:
    ThreadPool(int max_thread = MAX_THREAD,
               int max_queue = MAX_QUEUE):_max_thread(max_thread),
                _cur_thread(max_thread),
                _cap(max_queue),
                _stop_flag(false)
    {
        pthread_mutex_init(&_mutex, NULL);
        pthread_cond_init(&_full, NULL);
        pthread_cond_init(&_empty, NULL);
    }

    ~ThreadPool(){
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_full);
        pthread_cond_destroy(&_empty);
    }

    bool Start(){
        int i = 0;
        int ret = -1;
        pthread_t tid;
        for(i = 0; i < _max_thread; ++i)
        {
            ret = pthread_create(&tid, NULL, thr_start, (void*)this);
            if(ret != 0){
                printf("create thread error!\n");
                return false;
            }
            pthread_detach(tid);
        }
        return true;
    }

    bool stop(){
        thread_lock();
        if(_stop_flag == true){
            thread_unlock();
            return false;
        }

        while(_cur_thread > 0){
            _stop_flag = true;
            consumer_notice_all();
            productor_wait();
        }

        thread_unlock();
        return true;
    }
    
    bool AddTask(Task *task){
        thread_lock();

        while(queue_is_full()){
            consumer_notice();
            productor_wait();
        }

        _tlist.push(task);
        consumer_notice();

        thread_unlock();
        return true;
    }

    int get_size(){ return _tlist.size(); }
private:
    static void *thr_start(void *arg){
        ThreadPool *pool = (ThreadPool*)arg;
        while(1){
            pool->thread_lock();
            while(pool->queue_is_empty() && pool->thread_is_stop() == false){
                pool->productor_notice();
                pool->consumer_wait();
            }

            if(pool->queue_is_empty() && pool->thread_is_stop()){
                pool->thread_exit();
            }
 
            Task *task;
            pool->queue_pop_data(&task);
            pool->thread_unlock();

            task->Run(pool->get_size());
        }
        return NULL;
    }

    bool queue_pop_data(Task **task){
        *task = _tlist.front();
        _tlist.pop();
        return true;
    }

    void thread_exit(){
       _cur_thread--;
       thread_unlock();
       productor_notice_all();
       printf("%p is exit!\n", (void*)pthread_self());
       pthread_exit(NULL);
    }

    bool thread_is_stop(){
        return _stop_flag;
    }

    void thread_lock(){
        pthread_mutex_lock(&_mutex);
    }

    void thread_unlock(){
        pthread_mutex_unlock(&_mutex);
    }

    //任务队列为空则等待
    void consumer_wait(){
        pthread_cond_wait(&_empty, &_mutex);
    }

    void consumer_notice(){
        pthread_cond_signal(&_empty);
    }

    void consumer_notice_all(){
        pthread_cond_broadcast(&_empty);
    }
    void productor_wait(){
        pthread_cond_wait(&_full, &_mutex);
    }

    void productor_notice(){
        pthread_cond_signal(&_full);
    }

    void productor_notice_all(){
        pthread_cond_broadcast(&_full);
    }
    
    bool queue_is_empty(){
        return _tlist.empty();
    }

    bool queue_is_full(){
        return ((int)_tlist.size() == _cap);
    }
    int _max_thread;//最多有多少个线程
    int _cur_thread;//当前有多少个线程
    int _cap;
    bool _stop_flag;//线程池中线程的退出标志
    queue<Task *> _tlist;
    pthread_mutex_t _mutex;
    pthread_cond_t _empty;
    pthread_cond_t _full;
};

int main()
{
    ThreadPool t;
    t.Start();
    Task task[10];
    for(int i = 0; i < 10; ++i){
        task[i].SetData(i);
        t.AddTask(&task[i]);
    }
    t. stop();
    return 0;
}

