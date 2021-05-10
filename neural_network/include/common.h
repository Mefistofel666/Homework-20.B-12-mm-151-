#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include "data.h"

class common_data
{
protected:
    std::vector<data *> *training_data;
    std::vector<data *> *test_data;
    std::vector<data *> *validation_data;
public:
    void set_training_data(std::vector<data *> *vec);
    void set_test_data(std::vector<data *> *vec);
    void set_validation_data(std::vector<data *> *vec);


};

#endif