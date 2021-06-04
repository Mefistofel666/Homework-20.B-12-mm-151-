#include "neuron.h"
#include <random>

// генератор случайных чисел от min до max
double generateRandomNum(double min, double max)
{
    double random = (double) rand() / RAND_MAX; // от 0 до 1 
    return min + random * (max - min); // от max до min
}

// конструктор нейрона
Neuron::Neuron(int previousLayerSize ,int currentLayerSize)
{
    initializeWeigths(previousLayerSize);

}
// заполняем веса случайными числами от -1 до 1. 
void Neuron::initializeWeigths(int previousLayerSize)  
{
    for(int i = 0; i < previousLayerSize + 1; i++) // последнее значение это смещение(bias)
    {
        weights.push_back(generateRandomNum(-1.0,1.0));
    }
}
