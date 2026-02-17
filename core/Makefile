.PHONY: build run grammar clean test run-tests

MODULES_DIR := $(CURDIR)

test: clean runtime run-tests
build: clean run

run:
	@cd ./build && cmake .. -DENABLE_TESTING_FOR_TYPES_HINTS=OFF
	@cd ./build && make -j
	@#cd ./build && ./yogi ../inputs/main.io

dev:
	@cd ./build && cmake .. -DENABLE_TESTING_FOR_TYPES_HINTS=OFF
	@cd ./build && make -j
	@cd ./build && ./yogi ../inputs/dev.io


run-tests:
	@cd ./build && cmake .. -DENABLE_TESTING=ON
	@cd ./build && make -j run-tests


clean:
	@rm -rf build gen .idea && mkdir "build"

runtime:
	@clang++ -std=c++20 -O3 -emit-llvm -c \
	$(shell find $(MODULES_DIR) -type f -name "*.cpp") \
	-I $(MODULES_DIR) -o $(MODULES_DIR)/runtime.bc





