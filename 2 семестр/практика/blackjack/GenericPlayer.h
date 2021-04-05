#pragma once

#ifndef GENERICPLAYER_H
#define GENERICPLAYER_H

#include "Hand.h"
class GenericPlayer : public Hand
{
private:
    friend std::ostream &operator<<(std::ostream &os, const GenericPlayer &aGenericPlayer);

public:
    GenericPlayer(const std::string &name = "");
    virtual ~GenericPlayer();
    virtual bool is_hitting() const = 0;
    bool isBusted() const;
    void Bust() const;

protected:
    std::string m_name;
};

#endif