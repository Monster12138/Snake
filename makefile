client:controller.c view.c client.c
	gcc -I/usr/include/mysql $^ -L/usr/lib/mysql -lmysqlclient -o $@ -pthread
