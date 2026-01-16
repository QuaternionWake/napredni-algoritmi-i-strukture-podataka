main: main.c quadratic_probing.c quadratic_probing.h
	gcc -c main.c
	gcc -c quadratic_probing.c
	gcc -o main main.o quadratic_probing.o

interactive: interactive.c quadratic_probing.c quadratic_probing.h
	gcc -c interactive.c
	gcc -c quadratic_probing.c
	gcc -o interactive interactive.o quadratic_probing.o
	./interactive

run: main
	./main
