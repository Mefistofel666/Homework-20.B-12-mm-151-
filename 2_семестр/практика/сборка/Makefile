myprog: main.o insertion.o merge.o qsort.o
	g++ main.o insertion.o merge.o qsort.o -o myprog
insertion.o: insertion.cpp
	g++ -c insertion.cpp
merge.o: merge.cpp
	g++ -c merge.cpp
qsort.o: qsort.cpp
	g++ -c qsort.cpp
main.o: main.cpp mylib.h
	g++ -c main.cpp
clean:
	del *.o