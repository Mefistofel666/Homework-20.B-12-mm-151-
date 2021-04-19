#ifndef PAIR
#define PAIR
#include <ostream>

template<class T1, class T2> class pair;
template<class T1, class T2> std::ostream& operator<<(std::ostream &os, const pair<T1,T2>& p);


template <class T1, class T2>
struct pair
{
public:
    T1 first;
    T2 second;
    pair();                               // default constructor
    pair(const T1 &t1, const T2 &t2);     // constructor
    pair(const pair<T1, T2> &other_pair); // copy-constructor
    bool operator==(const pair<T1, T2> other_pair);
    bool operator!=(const pair<T1, T2> other_pair);
    void Swap(pair<T1, T2> &other_pair);
    friend std::ostream& operator<< <T1,T2>(std::ostream &os, const pair<T1, T2> &p);
};

template <class T1, class T2>
pair<T1, T2>::pair() : first(T1()), second(T2()){};

template <class T1, class T2>
pair<T1, T2>::pair(const T1 &t1, const T2 &t2) : first(t1), second(t2){};

template <class T1, class T2>
pair<T1, T2>::pair(const pair<T1, T2> &other_pair) : first(other_pair.first), second(other_pair.second){};

template <class T1, class T2>
bool pair<T1, T2>::operator==(const pair<T1, T2> other_pair)
{
    return (first == other_pair.first && second == other_pair.second);
}

template<class T1, class T2>
void pair<T1, T2>::Swap(pair<T1,T2> &other_pair)
{
    T1 tmp1 = first;
    first = other_pair.first;
    other_pair.first = tmp1;
    T2 tmp2 = second;
    second = other_pair.second;
    other_pair.second = tmp2;
}

template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, const pair<T1, T2> &p)
{
    if (p.first)
        os << "(" <<p.first << ", ";
    else
        os << "( empty";
    if (p.second)
        os << p.second << ")";
    else
        os << " empty )";
    return os;
}
#endif