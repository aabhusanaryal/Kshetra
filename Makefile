all: compile link

compile:
	g++ -Isrc/include -c -g *.cpp

link:
	g++ *.o -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -o main.exe