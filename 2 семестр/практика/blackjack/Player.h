#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "GenericPlayer.h"

class Player : public GenericPlayer
{
public:
    Player(const std::string &name = "");
    virtual ~Player();
    virtual bool is_hitting() const;
    void win() const;
    void lose() const;
    void push() const;
};

#endif