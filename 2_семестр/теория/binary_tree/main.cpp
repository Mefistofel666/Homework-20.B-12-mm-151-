#include "binary_tree.h"

int main()
{
    SearchTree *tree = new SearchTree(4);
    tree->insert(2);
    tree->insert(5);
    tree->insert(1);
    tree->insert(3);
    tree->insert(7);
    tree->insert(6);
    tree->insert(8);
    tree->inOrderTraversal("cout");
    std::cout << "\n";
    tree->BFS();
    std::cout << "\n";

    return 0;
}