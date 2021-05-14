#include <iostream>
#include <string>

struct Node
{
    std::string data;
    Node *next = 0;
};
class Stack
{
public:
    Node *head;
    Stack(std::string x);
    ~Stack();
    void push(std::string x);
    std::string pop();
};

Stack::Stack(std::string x)
{
    head = new Node;
    head->data = x;
}

Stack::~Stack()
{
    while (head)
    {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
}

void Stack::push(std::string x)
{
    Node *tmp = new Node;
    tmp->next = head;
    tmp->data = x;
    head = tmp;
}

std::string Stack::pop()
{
    if (!head)
    {
        std::cerr << "Stack is empty";
        return 0;
    }
    Node *tmp = head;
    head = head->next;
    std::string res = tmp->data;
    delete tmp;
    return res;
}