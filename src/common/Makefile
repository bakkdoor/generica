OBJS	= gobject.o functions.o eval.o utils.o hash.o

CC	= gcc
CFLAGS	= -g -Wall -ansi -pedantic

all: $(OBJS)

gobject.o: gobject.c
	$(CC) $(CFLAGS) -c gobject.c -o gobject.o

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c -o functions.o

eval.o: eval.c
	$(CC) $(CFLAGS) -c eval.c -o eval.o

utils.o: utils.c includes.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o

hash.o: hash.c includes.h
	$(CC) $(CFLAGS) -c hash.c -o hash.o

clean:
	rm -f *.o
