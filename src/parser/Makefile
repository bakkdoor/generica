# Makefile

OBJS	= bison.o lex.o

CC	= gcc
CFLAGS	= -g -Wall -ansi -pedantic

all:		$(OBJS)

lex.o:		lex.c
		$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c:		generica.lex
		flex generica.lex
		cp lex.yy.c lex.c

bison.o:	bison.c
		$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c:	generica.y
		bison -d -v generica.y
		cp generica.tab.c bison.c
		cmp -s generica.tab.h tok.h || cp generica.tab.h tok.h

lex.o yac.o	: includes.h ../common/includes.h
lex.o		: tok.h

clean:
	rm -f *.o *~ lex.c lex.yy.c bison.c tok.h generica.tab.c generica.tab.h generica.output

