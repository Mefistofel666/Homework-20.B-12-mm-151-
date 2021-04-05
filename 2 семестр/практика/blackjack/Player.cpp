#include "Player.h"

Player::Player(const std::string &name) : GenericPlayer(name) {}

Player::~Player() {}

bool Player::is_hitting() const
{
    std::cout << m_name << " do you want a hit?(y/n)";
    char response;
    std::cin >> response;
    return (response == 'y' || response == 'Y');
}
void Player::win() const
{
    std::cout << m_name << " wins.\n";
}

void Player::lose() const
{
    std::cout << m_name << " loses.\n";
}
void Player::push() const
{
    std::cout << m_name << " pushes.\n";
}