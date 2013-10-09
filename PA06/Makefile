all: pa06

pa06: answer.o pa06.o
	gcc pa06.o answer06.o -o pa06

pa06.o: pa06.c pa06.h
	gcc -g -Wall -Wshadow -c pa06.c

answer.o: answer06.c pa06.h
	gcc -g -Wall -Wshadow -c answer06.c

clean:
	rm -rf *.o pa06
