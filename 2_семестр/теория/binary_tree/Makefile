CC = g++

all: prog

prog:  objdir obj/binary_tree.o obj/main.o
	$(CC) obj/binary_tree.o obj/main.o -o prog
	rm -r obj
objdir:
	mkdir -p obj
obj/binary_tree.o: binary_tree.cpp 
	$(CC) -I binary_tree.h -c binary_tree.cpp -o obj/binary_tree.o 
obj/main.o: main.cpp
	$(CC) -I binary_tree.h -c main.cpp -o obj/main.o
clean:
	rm -r prog

