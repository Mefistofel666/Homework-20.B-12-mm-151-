#include "common.h"

void CommonData::setTrainingData(std::vector<Data *> *vec)
{
    trainingData = vec;
}
void CommonData::setTestData(std::vector<Data *> *vec)
{
    testData = vec;
}
void CommonData::setValidationData(std::vector<Data *> *vec)
{
    validationData = vec;
}