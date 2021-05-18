#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include <vector>

class Layer
{
public:
    int currentLayerSize;
    std::vector<Neuron *> neurons;
    std::vector<double> layerOutput;
    Layer(int, int);
    ~Layer();
    std::vector<double> getLayerOutputs();
    int getSize();
};

#endif