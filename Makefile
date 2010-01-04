TEST_FILES = conditionals.gna define.gna eval.gna lambda.gna lists.gna math.gna
TEST_CMD = clear; bin/generica examples/$(file); sleep 2;

all: generica

generica:
	cd src && make

test: generica
	$(foreach file, $(TEST_FILES), $(TEST_CMD))

clean:
	cd src && make clean > /dev/null
	rm -f bin/*
