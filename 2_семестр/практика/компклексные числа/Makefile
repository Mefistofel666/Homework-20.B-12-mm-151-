myprog: complex.o main.o
	g++ complex.o main.o -o myprog
complex.o: complex.cpp complex.h
	g++ -c complex.cpp
main.o: main.cpp 
	g++ -c main.cpp
clean:
	rm -r *.o