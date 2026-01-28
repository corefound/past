.PHONY: all build

build:
	@cd ./src/bindings/build && rm -rf ./* 
	@cd ./src/bindings && npx node-gyp configure
	@cd ./src/bindings && npx node-gyp build