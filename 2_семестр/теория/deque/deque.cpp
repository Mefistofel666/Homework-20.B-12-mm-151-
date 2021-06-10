struct Node
{
    int data;
    Node *next;
    Node *prev;
public:
    Node(int d):data(d), next(nullptr), prev(nullptr){};
    ~Node();
};
struct deque
{
    unsigned size;
    Node *head;
    Node *tail;
public:
    deque();
    ~deque();
    void push_front(int x);
	void push_back(int x);
	int pop_front();
	int pop_back();
};