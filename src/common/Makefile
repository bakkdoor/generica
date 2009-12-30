OBJS	= gobject.o functions.o eval.o utils.o

CC	= gcc
CFLAGS	= -g -Wall -ansi -pedantic

all: $(OBJS)

gobject.o: gobject.c
	$(CC) $(CFLAGS) -c gobject.c -o gobject.o

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c -o functions.o

eval.o: eval.c
	$(CC) $(CFLAGS) -c eval.c -o eval.o

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c -o utils.o

clean:
	rm -f *.o
