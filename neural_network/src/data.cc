#include "data.h"


// data::data()
// {
//     feature_vector = new std::vector<uint_fast8_t>;
// }
// data::~data()
// {
    
// }

void Data::setDistance(double val)
{
    distance = val;
}

void Data::setFeatureVector(std::vector<uint8_t> *vec)
{
    featureVector = vec;
}

void Data::setNormalizedFeatureVector(std::vector<double>* vec)
{
  normalizedFeatureVector = vec;
}

void Data::appendToFeatureVector(uint8_t val)
{
    featureVector->push_back(val);
}

void Data::appendToFeatureVector(double val)
{
    normalizedFeatureVector->push_back(val);
}

void Data::setLabel(uint8_t val)
{
    label = val;
}

void Data::setEnumeratedLabel(uint8_t val)
{
    enumeratedLabel = val;
}

void Data::setClassVector(int classCounts)
{
    classVector = new std::vector<int>();
    for(int i = 0; i < classCounts; i++)
    {
        if(i == label) classVector->push_back(1);
        else classVector->push_back(0);
    }
}

void Data::printVector()
{
    printf("[ ");
    for(uint8_t val : *featureVector)
    {
        printf("%u ", val);
    }
    printf("]\n");
}

void Data::printNormalizedVector()
{
  printf("[ ");
  for(auto val : *normalizedFeatureVector)
  {
    printf("%.2f ", val);
  }
  printf("]\n");
  
}

double Data::getDistance()
{
    return distance;
}

int Data::getFeatureVectorSize()
{
    featureVector->size();
}

uint8_t Data::getLabel()
{
    return label;
}

uint8_t Data::getEnumeratedLabel()
{
    return enumeratedLabel;
}

std::vector<uint8_t> *Data::getFeatureVector()
{
    return featureVector;
}

std::vector<int>  Data::getClassVector()
{
  return *classVector;
}

std::vector<double> * Data::getNormalizedFeatureVector()
{
  return normalizedFeatureVector;
}

