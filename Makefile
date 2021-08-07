all: compile link run

compile:
	g++ -Isrc/include -c -g -O2 *.cpp

link:
	g++ *.o -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -o main.exe

run:
	./main.exe