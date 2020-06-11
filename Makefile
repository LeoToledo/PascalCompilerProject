all: output clean

output: main.o lexico.o sintatico.o
	g++ -std=c++0x -Wall -o PascalCompExe main.o lexico.o sintatico.o

main.o: main.cpp lexico.h
	g++ -std=c++0x -c main.cpp

lexico.o: lexico.cpp lexico.h
	g++ -std=c++0x -c lexico.cpp

sintatico.o: sintatico.cpp sintatico.h
	g++ -std=c++0x -c sintatico.cpp

clean:
	rm -rf *.o