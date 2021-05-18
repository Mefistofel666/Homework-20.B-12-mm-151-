#ifndef _HIDDEN_LAYER_H
#define _HIDDEN_LAYER_H
#include "layer.h"

class HiddenLayer:public Layer
{
public:
    HiddenLayer(int prev, int current):Layer(prev, current){}
    void feedForward(Layer prev);
    void backProp(Layer next);
    void updateWeights(double, Layer *);
};

#endif