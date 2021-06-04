#ifndef LAYER_H
#define LAYER_H 

#include "neuron.h"
#include "stdint.h"
#include <vector>

class Layer
{
public:
    int currentLayerSize; // размер текущего слоя 
    std::vector<Neuron *> neurons; // нейроны в слое
    std::vector<double> layerOutputs; //выходы из нейронов в слое
    Layer(int prevLayerSize, int currLayerSize); // конструктор
    ~Layer(); // деструктор(надо фиксить)
};

#endif