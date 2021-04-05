#include "Deck.h"

Deck::Deck(){
    m_cards.reserve(52);
    populate();
}

Deck::~Deck(){}

void Deck::populate()
{
    Clear();
    for(int s = Card::CLUBS; s<=Card::SPADES;s++){
        for(int r = Card::ACE; r<= Card::KING; r++){
            add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }
}

void Deck::Shuffle()
{
    auto rng = std::default_random_engine{};
    std::shuffle(m_cards.begin(), m_cards.end(), rng);
}

void Deck::deal(Hand &aHand){
    if(!m_cards.empty()){
        aHand.add(m_cards.back());
        m_cards.pop_back();

    }else{
        std::cout << "Out of cards. Unable to deal.";
    }
}

void Deck::additional_cards(GenericPlayer &aGenericPlayer)
{
    std::cout << "\n";
    while(!(aGenericPlayer.isBusted())&&aGenericPlayer.is_hitting()){
        deal(aGenericPlayer);
        std::cout << aGenericPlayer << "\n";
        if(aGenericPlayer.isBusted()) aGenericPlayer.Bust();
    }
}