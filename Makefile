#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -g

#  Sources
SOURCES = zeruns.c

#  Objects
OBJECTS = zeruns.o

zeruns: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

clean::
	rm -f *.o core a.out zeruns *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
