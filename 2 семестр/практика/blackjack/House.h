#pragma once

#ifndef HOUSE_H
#define HOUSE_H

#include "GenericPlayer.h"

class House: public GenericPlayer
{
public:
    House(const std::string &name = "House");
    virtual ~House();
    virtual bool is_hitting() const;
    void flip_first_card();
};


#endif