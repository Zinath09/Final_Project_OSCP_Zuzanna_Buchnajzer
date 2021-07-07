All: main


main: main.c
	gcc main.c -lpthread
	./a.out
