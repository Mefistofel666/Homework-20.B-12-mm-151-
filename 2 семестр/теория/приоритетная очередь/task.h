#ifndef TASK
#define TASK

#include <string>
#include <vector>

struct task
{
    std::string name;
    double t_in;
    double t_work;
    int priority;
    task(std::string n = "", double in = 0, double out = 0, int prior = 0) : name(n), t_in(in), t_work(out), priority(prior){};
};

#endif