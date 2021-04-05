#include "Hand.h"

Hand::Hand()
{
    m_cards.reserve(7);
}
Hand::~Hand()
{
    Clear();
}

void Hand::add(Card *pCard)
{
    m_cards.push_back(pCard);
}

void Hand::Clear()
{
    std::vector<Card *>::iterator iter;
    for (iter = m_cards.begin(); iter != m_cards.end(); iter++)
    {
        delete *iter;
        *iter = 0;
    }
    m_cards.clear();
}

int Hand::get_total() const
{
    if (m_cards.empty())
        return 0;
    if (m_cards[0]->get_value() == 0)
        return 0;
    int total = 0;
    bool containsAce = false;
    std::vector<Card *>::const_iterator iter;
    for (iter = m_cards.begin(); iter != m_cards.end(); iter++)
    {
        total += (*iter)->get_value();
        if ((*iter)->get_value() == Card::ACE)
            containsAce = true;
    }

    if (containsAce && (total <= 11))
        total += 10;

    return total;
}