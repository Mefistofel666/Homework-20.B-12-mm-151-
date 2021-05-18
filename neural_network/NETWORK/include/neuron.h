#ifndef _NEURON_H
#define _NEURON_H

#include <cmath>
#include <vector>
class Neuron
{
private:
    std::vector<double> weights;
    double preActivation;
    double activatedOutput;
    double outputDerivative;
    double error;
    double alpha; // used in activation function
public:
    Neuron(int, int);
    ~Neuron();
    void initializeWeights(int previousLayerSize, int currentLayerSize);
    void setError(double);
    void setWeight(double, int);
    double calculatePreActivation(std::vector<double>);
    double activate();
    double calculateOutputDerivative();
    double sigmoid();
    double relu();
    double leakyRelu();
    double inverseSqrtRelu();
    double getOutput();
    double getOutputDerivative();
    double getError();
    std::vector<double> getWeights(); 
};

#endif