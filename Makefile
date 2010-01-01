all: generica

generica:
	cd src && make

test: generica
	clear
	bin/generica spec/spec.gna
clean:
	cd src && make clean > /dev/null
	rm -f bin/*
