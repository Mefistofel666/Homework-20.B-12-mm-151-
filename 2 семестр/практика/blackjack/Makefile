blackjack: main.o House.o Hand.o GenericPlayer.o Card.o Player.o Deck.o Game.o
	g++ main.o House.o Hand.o GenericPlayer.o Card.o Player.o Deck.o Game.o -o blackjack
house.o: House.cpp House.h
	g++ -c House.cpp
Hand.o: Hand.cpp Hand.h
	g++ -c Hand.cpp
GenericPlayer.o: GenericPlayer.cpp GenericPlayer.h
	g++ -c GenericPlayer.cpp
Card.o: Card.cpp Card.h
	g++ -c Card.cpp
Player.o: Player.cpp Player.h
	g++ -c Player.cpp
Deck.o: Deck.cpp Deck.h
	g++ -c Deck.cpp
Game.o: Game.cpp Game.h
	g++ -c Game.cpp
main.o: main.cpp 
	g++ -c main.cpp
clear:
	del *.o