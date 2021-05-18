#ifndef KNN_H
#define KNN_H

#include "common.h"

class KNN:public CommonData
{
    int k;
    std::vector<Data *> *neighbours;


public:
    KNN(int);
    KNN();
    ~KNN();

    void findKnearest(Data *queryPoint);
    void setK(int val);
    int findMostFrequentClass();


    int predict();
    double calculateDistance(Data *queryPoint, Data *input);
    double validatePerformance();
    double testPerformance();
};

#endif