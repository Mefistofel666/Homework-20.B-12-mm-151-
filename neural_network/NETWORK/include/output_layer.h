#ifndef _OUTPUT_LAYER_H
#define _OUTPUT_LAYER_H
#include "layer.h"
#include "data.h"
class OutputLayer:public Layer
{
public:
    OutputLayer(int prev, int current): Layer(prev, current){}
    void feedForward(Layer);
    void backProp(data *d);
    void updateWeights(double, Layer *);

};

#endif