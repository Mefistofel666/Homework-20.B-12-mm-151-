#include "binary_tree.h"

int main()
{
//             4
//         2       5
//     1      3        7
//                  6     8
// 
//     
    SearchTree *tree = new SearchTree(4);
    tree->insert(2);
    tree->insert(5);
    tree->insert(1);
    tree->insert(3);
    tree->insert(7);
    tree->insert(6);
    tree->insert(8);
    std::cout << "In ascending order: \n";
    tree->inOrderTraversal("cout");
    std::cout << "\n";
    std::cout << "By level: \n";
    tree->BFS();
    std::cout << "\n";

    return 0;
}