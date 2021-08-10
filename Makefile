all: compile link run

compile:
	g++ -Isrc/include -Isrc_SFML/include -c -g *.cpp

link:
	g++ *.o -Lsrc_SFML/lib -lsfml-graphics -lsfml-window -lsfml-system my.res -o main.exe

run:
	./main.exe