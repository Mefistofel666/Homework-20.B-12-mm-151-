#ifndef _NETWORK_H
#define _NETWORK_H

#include "data.h"
#include "neuron.h"
#include "layer.h"
#include "hidden_layer.h"
#include "output_layer.h"
#include "input_layer.h" 
#include "common.h"

class Network:public common_data
{
private:
    InputLayer *inputLayer;
    OutputLayer *outputLayer;
    std::vector<HiddenLayer *> hiddenLayers;
    double eta; // learning rate
public:
    Network(std::vector<int> hiddenLayerSpec, int,int);
    ~Network();
    void fprop(data *data);
    void bprop(data *data);
    void updateWeights();
    void train();
    void test();
    void validate();
};

#endif