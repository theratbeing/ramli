CC = gcc
CCFLAGS = -Iinc -std=c11 -Wall -Wextra -pedantic -fsanitize=address
DEFOBJS = objects.o generator.o curses_window.o

default : $(DEFOBJS) main.o
	$(CC) $(CCFLAGS) -lncursesw $(DEFOBJS) main.o -o ramli

test : $(DEFOBJS) debug.o
	$(CC) $(CCFLAGS) -lncursesw $(DEFOBJS) debug.o -o a.out

main.o : main.c
	$(CC) $(CCFLAGS) -c main.c

debug.o : debug.c
	$(CC) $(CCFLAGS) -c debug.c

generator.o : src/generator.c inc/generator.h
	$(CC) $(CCFLAGS) -c src/generator.c

objects.o : src/objects.c inc/objects.h
	$(CC) $(CCFLAGS) -c src/objects.c

curses_window.o : src/curses_window.c inc/curses_window.h
	$(CC) $(CCFLAGS) -c src/curses_window.c

clean :
	rm *.o
