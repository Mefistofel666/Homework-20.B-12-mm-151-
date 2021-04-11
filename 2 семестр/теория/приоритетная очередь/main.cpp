#include <iostream>
#include "b_heap.h"
#include <algorithm>

bool cmp(task a, task b)
{
    return a.t_in < b.t_in;
}

int main()
{

    int n;
    std::cin >> n;

    std::string name;
    int prior;
    int t_in;
    int t_work;
    task tmp;
    std::vector<task> tasks;

    for (int i = 0; i < n; i++)
    {
        std::cin >> name >> prior >> t_in >> t_work;
        tmp.name = name;
        tmp.priority = prior;
        tmp.t_in = t_in;
        tmp.t_work = t_work;
        tasks.push_back(tmp);
    }

    std::sort(tasks.begin(), tasks.end(), cmp);

    binary_heap b_heap;

    int t = 0;

    while ((tasks.size() != 0) || (b_heap.prior_q.size() != 0))
    {
        t++;
        if (t == tasks[0].t_in)
        {
            b_heap.insert(tasks[0]);
            tasks.erase(tasks.begin());
        }
        if (b_heap.prior_q.size() != 0)
        {
            b_heap.prior_q[0].t_work--;
            if (b_heap.prior_q[0].t_work == 0)
            {
                std::cout << b_heap.prior_q[0].name << " " << t << std::endl;
                b_heap.extract_min();
            }
        }
        if (t % 3 == 0)
        {
            for (int i = 0; i < b_heap.prior_q.size(); i++)
                b_heap.prior_q[i].priority--;
        }
    }





    return 0;
}