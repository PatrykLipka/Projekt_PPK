all : main
	
main : main.o funkcje.o
	g++ main.o funkcje.o -o main
main.o : main.cpp
	g++ -c main.cpp
funkcje.o : funkcje.cpp
	g++ -c funkcje.cpp
clean :
	rm -rf *o main
