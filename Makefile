all: output clean

output: main.o lexico.o
	g++ -std=c++0x -Wall -o LexicoExe main.o lexico.o

main.o: main.cpp lexico.h
	g++ -std=c++0x -c main.cpp

lexico.o: lexico.cpp lexico.h
	g++ -std=c++0x -c lexico.cpp

clean:
	rm -rf *.o