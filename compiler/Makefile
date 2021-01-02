.PHONY: all build_dirs clean debug release

all: debug

build_dirs:
	mkdir -p ./build

debug: build_dirs
debug:
	cd ./build && cmake ..
	cd ./build && make

clean:
	rm -rvf ./build/*
