all: pa06

pa06: answer.o
	gcc pa06.o answer06.o -o pa06

pa06.o: pa06.c pa06.h
	gcc -c pa06.c

answer.o: answer06.c
	gcc -c answer06.c
