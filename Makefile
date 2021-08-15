all: compile link run

compile:
	g++ -Isrc/include -Isrc_SFML/include -c -g -O2 ./src/*.cpp

link:
	g++ *.o -Lsrc_SFML/lib -lsfml-graphics -lsfml-window -lsfml-system ./assets/icon.res -Wl,--subsystem,windows -mwindows -o ./build_gcc/Kshetra.exe

run:
	./build_gcc/Kshetra.exe