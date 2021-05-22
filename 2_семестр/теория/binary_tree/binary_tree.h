#ifndef BINARY_TREE
#define BINARY_TREE

#include <iostream>
#include <vector>
#include <queue>

class Node
{
public:
    int data;
    Node *right;
    Node *left;
    Node *parent;
    Node(int _data):data(_data), right(nullptr), left(nullptr), parent(nullptr){}
};

class SearchTree
{
    Node *root;
public:
    SearchTree(int _data);
    ~SearchTree();
    
    // основные операции с деревом
    void insert(int x);
    bool search(int x);
    void inOrderTraversal(std::string action);
    void inOrderTraversal(std::string action, Node *r);
    void BFS();


    // вспомогательные функции
    void destroyNode(Node *node);
    void addTo(Node *r, int x);
    bool findIn(Node *r, int x);
    Node *findNode(int x, Node *r);

};

#endif

