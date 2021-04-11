#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include "task.h"

struct binary_heap
{
    std::vector<task> prior_q;

    binary_heap(std::vector<task> q = {}) : prior_q(q){};
    binary_heap sift_down(int i);
    binary_heap sift_up(int i);
    int extract_min();
    binary_heap insert(task t);
};

#endif