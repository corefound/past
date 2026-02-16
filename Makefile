.PHONY: build run grammar clean test run-tests

MODULES_DIR := $(CURDIR)/src/modules

test: clean grammar runtime run-tests
build: clean grammar runtime run

run:
	@cd ./build && cmake .. -DENABLE_TESTING_FOR_TYPES_HINTS=OFF
	@cd ./build && make -j
	@cd ./build && ./yogi ../inputs/main.io

dev:
	@cd ./build && cmake .. -DENABLE_TESTING_FOR_TYPES_HINTS=OFF
	@cd ./build && make -j
	@cd ./build && ./yogi ../inputs/dev.io


run-tests:
	@cd ./build && cmake .. -DENABLE_TESTING=ON
	@cd ./build && make -j run-tests


grammar:
	@cd ./src/antlr/tokens && antlr -Dlanguage=Cpp Tokens.g4 -o ../generated/ -visitor
	@cd ./src/antlr/grammars && antlr -Dlanguage=Cpp Grammar.g4 -o ../generated/ -visitor

clean:
	@rm -rf build gen .idea && mkdir "build"
	@cd ./src/antlr && rm -rf generated .antlr *.tokens *.tokens.txt
	@cd ./src/antlr/tokens && rm -rf generated .antlr *.tokens *.tokens.txt

runtime:
	@clang++ -std=c++20 -O3 -emit-llvm -c \
	$(shell find $(MODULES_DIR) -type f -name "*.cpp") \
	-I $(MODULES_DIR) -o $(MODULES_DIR)/runtime.bc





