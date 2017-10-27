all: main

main: main.o polynomial.o 
	g++ -std=c++11 -g main.o polynomial.o  -o main
	
main.o: main.cpp polynomial.h
	g++ -std=c++11 -c main.cpp

polynomial.o: polynomial.cpp polynomial.h
	g++ -std=c++11 -c polynomial.cpp
    
 clean:
	rm *.o
	rm main
