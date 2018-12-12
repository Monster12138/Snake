main:controller.c view.c
	gcc -I/usr/include/mysql $^ -L/usr/lib/mysql -lmysqlclient -o $@ -pthread
