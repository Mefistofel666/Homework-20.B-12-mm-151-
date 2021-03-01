myProg: main.o qsort.o swap.o
	g++ main.o qsort.o swap.o -o myProg

swap.o: swap.cpp
	g++ -c swap.cpp
qsort.o: swap.h qsort.cpp
	g++ -c qsort.cpp
main.o: qsort.h main.cpp
	g++ -c main.cpp

clean:
	rm -f myProg *.o 

