all: generica

generica:
	cd src && make

test: generica
	clear
	bin/generica examples/lists.gna
clean:
	cd src && make clean > /dev/null
	rm -f bin/*
