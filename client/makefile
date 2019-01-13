.POINY:client
client:socket.c controller.c view.c client.c
	gcc -Wall -std=c++11 -I./include/mysql $^ -L./lib/mysql -lmysqlclient -o $@ -pthread
.POINY:clean
clean:
	rm -rf client
