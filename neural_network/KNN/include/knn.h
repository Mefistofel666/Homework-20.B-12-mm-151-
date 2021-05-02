#ifndef KNN_H
#define KNN_H

#include <vector>
#include <data.h>

class knn
{
    int k;
    std::vector<data *> *neighbours;
    std::vector<data *> *training_data;
    std::vector<data *> *test_data;
    std::vector<data *> *validation_data;

public:
    knn(int);
    knn();
    ~knn();

    void find_knearest(data *query_point);
    void set_training_data(std::vector<data *> *vec);
    void set_test_data(std::vector<data *> *vec);
    void set_validation_data(std::vector<data *> *vec);
    void set_k(int val);

    int predict();
    double calculate_distance(data *query_point, data *input);
    double validate_performance();
    double test_performance();
};

#endif