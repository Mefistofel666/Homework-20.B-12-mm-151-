#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include "data.h"

class CommonData
{
protected:
    std::vector<Data *> *trainingData;
    std::vector<Data *> *testData;
    std::vector<Data *> *validationData;
public:
    void setTrainingData(std::vector<Data *> *vec);
    void setTestData(std::vector<Data *> *vec);
    void setValidationData(std::vector<Data *> *vec);
};

#endif