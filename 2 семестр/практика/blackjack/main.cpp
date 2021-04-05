#include <vector>
#include "Game.h"

int main()
{

    std::cout << "Welcome to BlackJack! \n\n";
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        std::cout << "How many players? (1-7)";
        std::cin >> numPlayers;
    }
    std::vector<std::string> names;
    std::string name;
    for (int i = 0; i < numPlayers; i++)
    {
        std::cout << "Enter player name: ";
        std::cin >> name;
        names.push_back(name);
    }
    std::cout << "\n";

    Game aGame(names);

    char again = 'y';
    while (again != 'n' || again != 'N')
    {
        aGame.Play();
        std::cout << "\nDo you want to play again? (y/n)";
    }

    return 0;
}