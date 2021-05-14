#include <iostream>
#include <vector>

using std::vector;

void insertion_sort(vector<int> &x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = i; (j > 0) && x[j - 1]> x[j]; j--)
        {
            std::swap(x[j - 1], x[j]);
        }
    }
}