cc = gcc
cc_flags = -g -Wall -ansi -pedantic

files = common/gobject common/functions common/eval common/utils parser/lex parser/bison main
src_files = $(foreach file, $(files), $(file).c)
obj_files = $(foreach file, $(files), $(file).o)
build_cmd =  $(cc) $(cc_flags) -c $(file).c -o $(file).o

sub_dirs = common parser

all: subdirs ../bin/generica

../bin/generica: main.o
	$(cc) $(cc_flags) $(obj_files) -o ../bin/generica -lfl

main.o: $(foreach file, $(files), $(file).c) parser/generica.lex parser/generica.y
	$(cc) $(cc_flags) -c main.c -o main.o

subdirs:
	$(foreach dir, $(sub_dirs), cd $(dir) && make && cd ..;)

clean:
	$(foreach dir, $(sub_dirs), cd $(dir) && make clean > /dev/null && cd ..;)
	rm -f *.o > /dev/null
