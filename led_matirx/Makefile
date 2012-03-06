snyh: gtkmatrixled.o main.c interface.o callback.o
	gcc -g `pkg-config --libs --cflags gtk+-2.0` interface.o callback.o gtkmatrixled.o main.c -o snyh
gtkmatrixled.o:gtkmatrixled.c gtkmatrixled.h 
	gcc -g  `pkg-config --libs --cflags gtk+-2.0` gtkmatrixled.c -c

interface.o:interface.c callback.o
	gcc -g `pkg-config --libs --cflags gtk+-2.0` interface.c -c
callback.o:callback.c
	gcc -g -std=c99 `pkg-config --libs --cflags gtk+-2.0` callback.c -c

clean: 
	rm -rfv *.o
