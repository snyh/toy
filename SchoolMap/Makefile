win: 
	[ -d ./build] || mkdir -p build
	cp ./mingw32.cmake build
	cd build/ && cmake -DCMAKE_TOOLCHAIN_FILE=./mingw32.cmake ../ && make
