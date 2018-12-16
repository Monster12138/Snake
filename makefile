all:client server
client:socket.c controller.c view.c client.c
	gcc -I/usr/include/mysql $^ -L/usr/lib/mysql -lmysqlclient -o $@ -pthread
server:socket.c server.c
	gcc $^ -o $@ -pthread
