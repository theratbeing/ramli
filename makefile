CC = gcc
CCFLAGS = -Iinc -std=c11 -Wall -Wextra -pedantic -fsanitize=address

debug : objects.o generator.o debug.o
	$(CC) $(CCFLAGS) objects.o generator.o debug.o -o a.out

debug.o : debug.c
	$(CC) $(CCFLAGS) -c debug.c

generator.o : src/generator.c inc/generator.h
	$(CC) $(CCFLAGS) -c src/generator.c

objects.o : src/objects.c inc/objects.h
	$(CC) $(CCFLAGS) -c src/objects.c

clean :
	rm *.o
