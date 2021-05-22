#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node *prev;
    Node():data(0), next(nullptr), prev(nullptr){};
    Node(int d):data(d), next(nullptr), prev(nullptr){};
};

class CList
{
    Node *head;
public:
    CList();
    ~CList();
    CList(const CList & A);
    const CList &operator=(const CList &A);
    void push_back(int x);
    int pop_back();
    int getMax();
};

CList::CList()
{
    head = nullptr;
}
CList::~CList()
{
    if(!head) return;
    Node *p = head->next;
    while(p!=head)
    {
        Node *tmp = p;
        p = p->next;
        delete tmp;
    }
    delete head;
}


int CList::getMax()
{
    int max = head->data;
    Node* p = head->next;
    while (p != head)
    {
        if (p->data > max) max = p->data;
        p = p->next;
    }
    return max;
}


void CList::push_back(int x)
{
    if (head == nullptr)
    {
        head = new Node;
        head->data = x;
    }
    else if (head->next == nullptr)
    {
        Node* p = new Node;
        p->data = x;
        head->next = p;
        head->prev = p;
        p->next = head;
        p->prev = head;
    }
    else
    {
        Node* p = new Node;
        p->next = head;
        p->prev = head->prev;
        p->prev->next = p;
        head->prev = p;
        p->data = x;
    }
}

int CList::pop_back()
{
    Node* current = head->prev;
    head->prev = current->prev;
    current->prev->next = head;
    int res = current->data;
    delete current;
    return res;
}


int main() {
    CList list;
    for (int i = 0; i < 9; i++) 
        list.push_back(i);

    list.push_back(-5);
    std::cout << "elements: ";
    for (int i = 0; i < 9; i++)
        std::cout << i << " ";

    std::cout << -5 << "\n";

    std::cout << "current max: " << list.getMax() << "\n";
    int deleted_val = list.pop_back();
    std::cout << "elements: ";
    for (int i = 0; i < 9; i++)
        std::cout << i << " ";
    std::cout << "\n";
    std::cout << "current max: " << list.getMax() << "\n";

    return 0;
}