.PHONY: all build rebuild check test clean

all: clean check build test

clean:
	rm -rf build

build:
	./build.sh

rebuild: clean build

check:
	./run_linters.sh

test:
	./build.sh
	./run_tests.sh
