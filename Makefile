all: generica

generica:
	cd src && make

test: generica
	clear
	bin/generica examples/conditionals.gna
	sleep 2
	clear
	bin/generica examples/define.gna
	sleep 2
	clear
	bin/generica examples/lists.gna
	sleep 2
	clear
	bin/generica examples/math.gna
clean:
	cd src && make clean > /dev/null
	rm -f bin/*
