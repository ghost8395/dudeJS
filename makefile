CXX = ccache g++
OUTPUT_FILE=bin/myOwnNodeJS

define INCLUDE
	v8/include/
endef

define INCLUDEUV
	libuv/include/
endef

define APP
	app/index.cc
endef
 
define OBJ
	v8/libv8_monolith.a
	libuv/libuv-x86_64-gitpod.a
endef

export INCLUDE
export INCLUDEUV
export OUTPUT_FILE

export APP
export LIB
export OBJ
export APP


# will replace all the variable on line number 37 such as APP OBJ(executable monolith for v8 and libuv) INCLUDE(including header for v8) INCLUDEUV(including header for libuv) OUTPUT_FILE(path for output file)
# will output the exectuable to ./bin folder
build:
	npm i -g nodemon --silent
	sudo apt-get install -y ccache
	mkdir -p bin
	$(CXX) $$APP -I $$INCLUDE -I $$INCLUDEUV  -std=c++17 -pthread -o $$OUTPUT_FILE -DV8_COMPRESS_POINTERS $$OBJ -Wl,--no-as-needed -ldl

recompile:
	$(CXX) $$APP -I $$INCLUDE -I $$INCLUDEUV  -std=c++17 -pthread -o $$OUTPUT_FILE -DV8_COMPRESS_POINTERS $$OBJ -Wl,--no-as-needed -ldl
	
# watches all the files with cc,h,js,cpp,hpp for changes sand rebuilds the project
run:
	nodemon -e cc,h,js,cpp,hpp --exec "make recompile && ./bin/myOwnNodeJS index.js"

clean:
	rm -rf bin