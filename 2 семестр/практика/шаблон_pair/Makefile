CC = g++

PROG := prog.exe

all: $(PROG)

$(PROG): main.o
	$(CC) main.o -o $(PROG)

main.o: main.cpp 
	$(CC) -c main.cpp

clean:
	del *.o