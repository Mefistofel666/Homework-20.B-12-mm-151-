#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "House.h"
#include "Player.h"
#include <vector>
#include <ctime>


class Game
{
public:
    Game(const std::vector<std::string> &names);
    ~Game();
    void Play();
private:
    Deck m_deck;
    House m_house;
    std::vector<Player> m_players;
};



#endif