#include "binary_tree.h"


SearchTree::SearchTree(int _data)
{
    root = new Node(_data);
}
SearchTree::~SearchTree()
{
    destroyNode(root);
}
void SearchTree::destroyNode(Node *node)
{
    if(node)
    {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}
void SearchTree::insert(int x)
{   
    if(root == nullptr)
    {
        root = new Node(x);
    }else
    {
        addTo(root, x);
    }

}

void SearchTree::addTo(Node *r, int x)
{
    if(x < r->data)
    {
        if(r->left != nullptr)
        {
            addTo(r->left, x);
        }else
        {
            r->left = new Node(x);
            r->left->parent = r;
        }
    }else
    {
        if(r->right != nullptr)
        {
            addTo(r->right, x);
        }else
        {
            r->right = new Node(x);
            r->right->parent = r;
        }
    }
}

bool SearchTree::search(int x)
{   
    if(root == nullptr)
    {
        return 0;
    }else
    {
        findIn(root, x);
    }
    
}
bool SearchTree::findIn(Node *r, int x)
{
    if(r != nullptr)
    {
        if(x == r->data) return 1;
        if(x < r->data )
        {
            if(r->left != nullptr)
                return findIn(r->left, x);
            else return 0;
        }
        if(x > r->data)
        {
            if(r->right != nullptr)
                return findIn(r->right, x);
            else return 0;
        }
    }else return 0;
}

Node *SearchTree::findNode(int x, Node *r)
{
    if(!search(x)) return nullptr;
    else
    {
        Node *current = r;
        while(current != nullptr)
        {
            if(x == current->data) break;
            else if(x < current->data)
            {
                current = current->left;
            } else current = current->right;
        }
        return current;
    }
}


void SearchTree::inOrderTraversal(std::string action)
{
    inOrderTraversal(action, root);
}
void SearchTree::inOrderTraversal(std::string action, Node *r)
{
    if(r != nullptr)
    {
        inOrderTraversal(action, r->left);
        if(action == "cout")
        {   
            std::cout << r->data << " ";
        }
        inOrderTraversal(action, r->right);
    }
}

void SearchTree::BFS()
{
    std::vector<int> tmp;
    std::queue<Node> nodesQueue;
    nodesQueue.push(*root);
    while(!nodesQueue.empty())
    {
        Node current = nodesQueue.front();
        nodesQueue.pop();
        tmp.push_back(current.data);
        if(current.left != nullptr)
        {
            nodesQueue.push(*current.left);
        }
        if(current.right != nullptr)
        {
            nodesQueue.push(*current.right);
        }
    }
    for(int i = 0; i < tmp.size(); i++)
    {
        std::cout << tmp[i] << " ";
    }
}
