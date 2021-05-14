#pragma once

#ifndef HAND_H
#define HAND_H


#include "Card.h"
#include <vector>
class Hand
{
public:
    Hand();
    virtual ~Hand();
    void add(Card *pCard);
    void Clear();
    int get_total() const;

protected:
    std::vector<Card *> m_cards;
};

#endif