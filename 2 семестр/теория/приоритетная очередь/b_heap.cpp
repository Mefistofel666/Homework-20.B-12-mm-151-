#include "b_heap.h"

binary_heap binary_heap::sift_down(int i)
{
    while (2 * i + 1 < prior_q.size())
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = right;
        if (right < prior_q.size() && (prior_q[right].priority < prior_q[left].priority))
            j = right;
        if (prior_q[i].priority <= prior_q[j].priority)
            break;
        std::swap(prior_q[i], prior_q[j]);
        i = j;
    }
    return *this;
}

binary_heap binary_heap::sift_up(int i)
{
    while (prior_q[i].priority < prior_q[(i - 1) / 2].priority)
        std::swap(prior_q[i].priority, prior_q[(i - 1) / 2].priority);
    i = (i - 1) / 2;
    return *this;
}

int binary_heap::extract_min()
{
    int min = prior_q[0].priority;
    prior_q[0] = prior_q[prior_q.size() - 1];
    prior_q.erase(prior_q.begin());
    sift_down(0);
    return min;
}

binary_heap binary_heap::insert(task t)
{
    prior_q.push_back(t);
    sift_up(prior_q.size() - 1);
    return *this;
}