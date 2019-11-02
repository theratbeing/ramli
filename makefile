CC = gcc
CCFLAGS = -Iinc -std=c11 -Wall -Wextra -pedantic -g -fsanitize=address
LDFLAGS = -lncursesw
DEFOBJS = curses_window.o generator.o objects.o

default : main.o $(DEFOBJS)
	$(CC) $(CCFLAGS) main.o $(DEFOBJS) -o ramli $(LDFLAGS)

test : debug.o $(DEFOBJS)
	$(CC) $(CCFLAGS) debug.o $(DEFOBJS) -o a.out $(LDFLAGS)

main.o : main.c
	$(CC) $(CCFLAGS) -c main.c

debug.o : debug.c
	$(CC) $(CCFLAGS) -c debug.c

curses_window.o : src/curses_window.c inc/curses_window.h
	$(CC) $(CCFLAGS) -c src/curses_window.c

generator.o : src/generator.c inc/generator.h
	$(CC) $(CCFLAGS) -c src/generator.c

objects.o : src/objects.c inc/objects.h
	$(CC) $(CCFLAGS) -c src/objects.c

clean :
	rm *.o
