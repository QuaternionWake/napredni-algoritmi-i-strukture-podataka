MAKEFLAGS += --no-builtin-rules

c_files = \
	division_method.c \
	folding_method.c \
	main.c \
	quadratic_probing.c \
	words.c \
	double_hashing.c \
	linear_probing.c \
	mid-square_method.c \
	separate_chaining.c

main: m1 m2 m3 m4 m5 m6

m1: $(c_files)
	gcc main.c -lm -DMAX=20 -o main
	./main

m2: $(c_files)
	gcc main.c -lm -DMAX=50 -o main
	./main

m3: $(c_files)
	gcc main.c -lm -DMAX=100 -o main
	./main

m4: $(c_files)
	gcc main.c -lm -DMAX=200 -o main
	./main

m5: $(c_files)
	gcc main.c -lm -DMAX=500 -o main
	./main

m6: $(c_files)
	gcc main.c -lm -DMAX=1000 -o main
	./main
