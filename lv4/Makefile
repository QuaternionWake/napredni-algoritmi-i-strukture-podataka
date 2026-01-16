MAKEFLAGS += --no-builtin-rules

c_files = main.c ll.c sl.c

main: m1 m2 m3 m4 m5 m6

m1: $(c_files)
	gcc main.c -DN=10000 -o main
	./main

m2: $(c_files)
	gcc main.c -DN=100000 -o main
	./main

m3: $(c_files)
	gcc main.c -DN=500000 -o main
	./main

m4: $(c_files)
	gcc main.c -DN=1000000 -o main
	./main

m5: $(c_files)
	gcc main.c -DN=5000000 -o main
	./main

m6: $(c_files)
	gcc main.c -DN=10000000 -o main
	./main
