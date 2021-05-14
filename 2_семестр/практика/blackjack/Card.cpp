#include "Card.h"


Card::Card(rank r, suit s, bool ifu) : m_rank(r), m_suit(s), m_is_face_up(ifu) {}

int Card::get_value() const
{
    int value = 0;
    if (m_is_face_up)
    {
        value = m_rank;
        if (value > 10)
            value = 10;
    }
    return value;
}
void Card::flip(){
    m_is_face_up = !m_is_face_up;
}


std::ostream &operator<<(std::ostream &os, const Card &aCard){
    const std::string ranks[] = {"0", "Ace", "2", "3", "4", "5", "6", "7", "8","9", "10", "Jack", "Queen", "King"};
    const std::string suits[] = {"clubes", "diamonds", "hearts", "spades"};
    if(aCard.m_is_face_up){
        os << ranks[aCard.m_rank] << " of " <<suits[aCard.m_suit];
    }else{
        os << "XX";
    }
    return os;
}
