main: main.o Func.o File.o Parse.o
	g++ -g main.o Func.o File.o Parse.o -o main

main.o: main.cc
	g++ -c -g main.cc -o main.o
Func.o: Func.cc
	g++ -c -g Func.cc -o Func.o
File.o: File.cc
	g++ -c -g File.cc -o File.o
Parse.o: Parse.cc
	g++ -c -g Parse.cc -o Parse.o