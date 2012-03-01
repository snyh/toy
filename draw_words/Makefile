all:gend.c 
	gcc -o gend -g gend.c  `pkg-config --libs --cflags freetype2` `pkg-config --libs --cflags glib-2.0`

target="i686-pc-mingw32-"
win:gend.c 
	i686-pc-mingw32-gcc -o gend.exe  gend.c  `$(target)pkg-config --libs --cflags freetype2` `$(target)pkg-config --libs --cflags glib-2.0`
