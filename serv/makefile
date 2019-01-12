.PHONY:all
all:clean server
server:socket.cpp server.cpp
	g++ -Wall -std=c++11 -I./include/mysql $^ -L/usr/local/mysql/lib -lmysqlclient -o $@ -pthread
.PHONY:clean
clean:
	rm -rf server
