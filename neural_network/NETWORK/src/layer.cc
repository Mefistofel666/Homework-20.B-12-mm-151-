#include "layer.h"
// просто функция создающая слой: 
// в каждый нейрон текущего слоя входит столько элементов сколько было в предыдущем (полный двудольный граф по сути)
Layer::Layer(int previousLayerSize, int currentLayerSize)
{
    for(int i = 0 ; i < currentLayerSize; i++)
    {
        // 2 параметр для создания нейрона не нужен по сути, но фиксить прям лень
        neurons.push_back(new Neuron(previousLayerSize,currentLayerSize)); 
    }
    this->currentLayerSize = currentLayerSize;
}