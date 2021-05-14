myprog: main.o LoopArray.o
	g++ main.o LoopArray.o -o myprog
LoopArray.o: LoopArray.cpp LoopArray.h 
	g++ -c LoopArray.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	del *.o