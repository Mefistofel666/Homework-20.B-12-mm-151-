#ifndef DECK_H
#define DECK_H

#include "Hand.h"
#include "GenericPlayer.h"
#include <algorithm>
#include <random>

class Deck:public Hand
{
public:
    Deck();
    virtual ~Deck();
    void populate();
    void Shuffle();
    void deal(Hand &aHand);
    void additional_cards(GenericPlayer &aGenericPlayer);
};


#endif