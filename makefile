CC = gcc
CCFLAGS = -Iinc -std=c11 -Wall -Wextra -pedantic -fsanitize=address

debug : virtues.o generator.o debug.o
	$(CC) $(CCFLAGS) virtues.o generator.o debug.o -o debug

debug.o : debug.c
	$(CC) $(CCFLAGS) -c debug.c

generator.o : src/generator.c inc/generator.h
	$(CC) $(CCFLAGS) -c src/generator.c

virtues.o : src/virtues.c inc/virtues.h
	$(CC) $(CCFLAGS) -c src/virtues.c

clean :
	rm *.o
