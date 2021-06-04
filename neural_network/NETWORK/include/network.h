#ifndef _NETWORK_H
#define _NETWORK_H

#include "data.h"
#include "neuron.h"
#include "layer.h"
#include "common.h"

class Network:public CommonData
{
public:
    std::vector<Layer *> layers;
    double learningRate; // коэффициент скорости обучение
    double testPerformance; 
    Network(std::vector<int> spec, int inputSize, int numClasses, double learningRate);
    ~Network();
    std::vector<double> fprop(Data *data);
    double activate(std::vector<double>, std::vector<double>); // dot product
    double transfer(double);
    double transferDerivative(double); // used for backpropogation
    void bprop(Data *data); // обратное распросранение
    void updateWeights(Data *data);
    int predict(Data *data); // return the index of the maximum value int the output array
    void train(int);
    double test();
    void validate();
};

#endif