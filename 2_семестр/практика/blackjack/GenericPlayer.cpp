#include "GenericPlayer.h"
GenericPlayer::GenericPlayer(const std::string &name) : m_name(name) {}

GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::isBusted() const
{
    return (get_total() >= 21);
}
void GenericPlayer::Bust() const
{
    std::cout << m_name << " busts.\n";
}


std::ostream &operator<<(std::ostream &os, const GenericPlayer &aGenericPlayer){
    os << aGenericPlayer.m_name << ":\t";
    std::vector <Card *>::const_iterator pCard;
    if(!aGenericPlayer.m_cards.empty()){
        for(pCard= aGenericPlayer.m_cards.begin(); pCard!=aGenericPlayer.m_cards.end(); pCard++){
            os << *(*pCard) << "\t";
        }
        if(aGenericPlayer.get_total()!=0) std::cout << "(" << aGenericPlayer.get_total() << ")";

    }else{
        os << "<empty>";
    }
    return  os;
}
