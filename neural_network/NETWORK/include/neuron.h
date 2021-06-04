#ifndef _NEURON_H
#define _NEURON_H

#include <cmath>
#include <stdio.h>
#include <vector>
class Neuron
{
public:
    double output; // выход нейрона
    double delta; // "поправка" узла
    std::vector<double> weights; //вектор весов; последнее значение это смещение (bias)
    Neuron(int prevLayerSize,int currLayerSize); // конструктор нейрона
    void initializeWeigths(int prevLayerSize);  // заполнение весов случайными числами
};

#endif