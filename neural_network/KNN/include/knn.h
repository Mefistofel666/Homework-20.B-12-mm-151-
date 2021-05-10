#ifndef KNN_H
#define KNN_H

#include "common.h"

class knn:public common_data
{
    int k;
    std::vector<data *> *neighbours;


public:
    knn(int);
    knn();
    ~knn();

    void find_knearest(data *query_point);
    
    void set_k(int val);

    int predict();
    double calculate_distance(data *query_point, data *input);
    double validate_performance();
    double test_performance();
};

#endif