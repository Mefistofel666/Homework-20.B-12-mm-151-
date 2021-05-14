#include "Game.h"

Game::Game(const std::vector<std::string> &names)
{
    std::vector<std::string>::const_iterator pName;
    for(pName = names.begin(); pName!=names.end(); pName++){
        m_players.push_back(Player(*pName));
    }
    srand(static_cast<unsigned int>(time(0)));
    m_deck.populate();
    m_deck.Shuffle();
}
Game::~Game(){}

void Game::Play(){
    std::vector<Player>::iterator pPlayer;
    for(int i = 0; i<2; i++){
        for(pPlayer= m_players.begin(); pPlayer!=m_players.end(); pPlayer++){
            m_deck.deal(*pPlayer);

        }
        m_deck.deal(m_house);
    }
    m_house.flip_first_card();

    for(pPlayer = m_players.begin(); pPlayer!= m_players.end();pPlayer++){
        std::cout << *pPlayer << "\n";
    }
    std::cout << m_house;

    for(pPlayer = m_players.begin(); pPlayer!=m_players.end();pPlayer++){
        m_deck.additional_cards(*pPlayer);
    } 
    m_house.flip_first_card();
    std::cout << "\n" << m_house;

    m_deck.additional_cards(m_house);

    if(m_house.isBusted()){
        for(pPlayer = m_players.begin(); pPlayer!=m_players.end(); pPlayer++){
            if(!(pPlayer->isBusted())) pPlayer->win();
        }
    }
    else{
        for(pPlayer = m_players.begin(); pPlayer!=m_players.end();pPlayer++){
            if(!(pPlayer->isBusted())){
                if(pPlayer->get_total()>= m_house.get_total()){
                    pPlayer -> win();
                }
                else if(pPlayer-> get_total() < m_house.get_total()){
                    pPlayer -> lose();
                }
                else{
                    pPlayer ->push();
                }
            }
        }
    }
    for(pPlayer = m_players.begin(); pPlayer!=m_players.end(); pPlayer++){
        pPlayer ->Clear();
    }
    m_house.Clear();

}