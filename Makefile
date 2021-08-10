all: compile link run

compile:
	g++ -Isrc/include -Isrc_SFML/include -c -g *.cpp

link:
	g++ *.o -Lsrc_SFML/lib -lsfml-graphics -lsfml-window -lsfml-system ./assets/icon.res -o Kshetra.exe

run:
	./Kshetra.exe