#ifndef _LAYER_LAYER_H
#define _LAYER_LAYER_H
#include "layer.h"
#include "data.h"

class InputLayer: public Layer
{
public:
    InputLayer(int prev, int current):Layer(prev, current){}
    ~InputLayer();
    void setLayerOutputs(data *d);
};

#endif