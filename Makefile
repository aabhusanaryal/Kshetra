all: compile link

compile:
	g++ -Isrc/include -c -g main.cpp

link:
	g++ main.o -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -o main.exe