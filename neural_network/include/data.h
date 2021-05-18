#ifndef DATA_H
#define DATA_H

#include <vector>
#include <stdint.h> // iunt_8t
#include <stdio.h>

class Data
{
    std::vector<uint8_t> *featureVector; // no class
    std::vector<double> *normalizedFeatureVector;
    std::vector<int> *classVector;
    uint8_t label;
    uint8_t enumeratedLabel;
    double distance;

public:
    // Data();
    // ~Data();

    void appendToFeatureVector(uint8_t);
    void appendToFeatureVector(double);

    void printVector();
    void printNormalizedVector();

    void setFeatureVector(std::vector<uint8_t> *);
    void setNormalizedFeatureVector(std::vector<double> *);
    void setClassVector(int counts);
    void setLabel(uint8_t);
    void setEnumeratedLabel(uint8_t);
    void setDistance(double val);

    int getFeatureVectorSize();
    double getDistance();
    uint8_t getLabel();
    uint8_t getEnumeratedLabel();
    std::vector<uint8_t> * getFeatureVector();
    std::vector<double> * getNormalizedFeatureVector();
    std::vector<int> getClassVector();

};

#endif