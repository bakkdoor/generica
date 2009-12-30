OBJS	= gobject.o functions.o

CC	= gcc
CFLAGS	= -g -Wall -ansi -pedantic

all: $(OBJS)

gobject.o: gobject.c
	$(CC) $(CFLAGS) -c gobject.c -o gobject.o

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c -o functions.o

clean:
	rm -f *.o
