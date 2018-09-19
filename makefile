controller:controller.o 
	gcc -o controller controller.o 
controller.o:controller.c controller.h 
	gcc -c controller.c 
.PHONY:clean 
clean: 
	rm controller controller.o 
