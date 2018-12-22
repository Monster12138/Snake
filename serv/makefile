.PHONY:all
all:clean server
server:socket.cpp server.cpp
	g++ -I./include/mysql $^ -L./lib/mysql -lmysqlclient -o $@ -pthread
.PHONY:clean
clean:
	rm -rf server
