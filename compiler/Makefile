.PHONY: all build_dirs clean debug test

all: debug

build_dirs:
	mkdir -p ./build

debug: build_dirs
debug:
	cd ./build && cmake ..
	cd ./build && make

test: debug
test:
	./build/test/wakitest -d yes

clean:
	rm -rvf ./build/*
