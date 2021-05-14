#include "House.h"
House::House(const std::string &name):GenericPlayer(name){}

House::~House(){}

bool House:: is_hitting() const
{
    return(get_total() >= 16);
}
void House:: flip_first_card()
{
    if(!m_cards.empty()) m_cards[0]->flip();
    else  std::cout << "No cards to flip!\n";
}