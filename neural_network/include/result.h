#ifndef RESULT_H
#define RESULT_H
class result
{
private:
    // for all
    int trainSize;
    double time;
    double performance;
    // for network
    int epochs;
    int layerSize;
    // for KNN and K-Means
    int k;
public:
    result(int trainSize_, double time_, double perf, int epochs_ = 0, int layerSize_ = 0, int k_ = 0): 
    trainSize(trainSize_), time(time_), performance(perf), epochs(epochs_), layerSize(layerSize_), k(k_){}
    int getTrainSize();
    double getTime();
    double getPerformance();
    int getEpochs();
    int getLayerSize();
    int getK();
};

#endif