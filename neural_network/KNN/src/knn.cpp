#include "../include/knn.h"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"
#include "data_handler.h"

KNN::KNN(int val)
{
    k = val;
}
KNN::KNN()
{
    // Nothing to do
}
KNN::~KNN()
{
    //Nothing to do
}

// O(KN)
// O(N^2) if K ~ N
// if K is small then O(N)
// We can find distance for all data-points and sort them => O(N * log N) because array sorting is O(N * log N) and that is // good if K ~ N

void KNN::findKnearest(Data *queryPoint)
{
    neighbours = new std::vector<Data *>;
    double min = std::numeric_limits<double>::max();
    double previous_min = min;
    int index;
    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < trainingData->size(); j++)
            {
                double distance = calculateDistance(queryPoint, trainingData->at(j));
                trainingData->at(j)->setDistance(distance);
                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbours->push_back(trainingData->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
        else
        {
            for (int j = 0; j < trainingData->size(); j++)
            {
                double distance = trainingData->at(j)->getDistance();
                if (distance > previous_min && distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbours->push_back(trainingData->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
    }
}

void KNN::setK(int val)
{
    k = val;
}

int KNN::findMostFrequentClass()
{
    std::map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbours->size(); i++)
    {
        if (class_freq.find(neighbours->at(i)->getLabel()) == class_freq.end())
        {
            class_freq[neighbours->at(i)->getLabel()] = 1;
        }
        else
        {
            class_freq[neighbours->at(i)->getLabel()]++;
        }
    }

    int best = 0;
    int max = 0;
    for(auto kv : class_freq)
    {
        if(kv.second > max)
        {
            max = kv.second;
            best = kv.first;
        }
    }
    delete neighbours;
    return best;
}
double KNN::calculateDistance(Data *queryPoint, Data *input)
{
    double distance = 0.0;
    if(queryPoint->getNormalizedFeatureVector()->size() != input->getNormalizedFeatureVector()->size())
    {
        printf("Vectors have different size.\n");
        exit(1);
    }
#ifdef EUCLID
    for (unsigned i = 0; i < queryPoint->getNormalizedFeatureVector()->size(); i++)
    {
        distance += pow(queryPoint->getNormalizedFeatureVector()->at(i) - input->getNormalizedFeatureVector()->at(i), 2);
    }
    return sqrt(distance);

#elif defined MANHATTAN
// PUT MANHATTAN IMPLEMENTATION HERE
#endif

    
}
double KNN::validatePerformance()
{
    double current_performance = 0;
    int count = 0;
    int data_index = 0;
    for(Data *query_point : *validationData)
    {
        findKnearest(query_point);
        int prediction = findMostFrequentClass();
        data_index++;
        printf("%d -> %d \n", prediction, query_point->getLabel());
        if(prediction == query_point->getLabel())
        {
            count++;
        }
        printf("Current Performance = %.3f %%\n",((double)count*100.0)/((double)data_index) );
    }
    current_performance =  ((double)count*100.0)/((double)validationData->size());
    printf("Valifation Performance for K =%d : %.3f %%\n", k,current_performance);
    return current_performance;
}
double KNN::testPerformance()
{
    double current_performance = 0;
    int count = 0;
    for(Data *query_point : *testData)
    {
        findKnearest(query_point);
        int prediction = findMostFrequentClass();
        if(prediction == query_point->getLabel())
        {
            count++;
        }
    }
    current_performance = ((double)count*100.0)/((double(testData->size())));
    printf("Tested Performance = %.3f %%\n", current_performance);
    return current_performance;
}

int main()
{
    DataHandler *dh = new DataHandler();
    dh->readInputData("../train-images-idx3-ubyte");
    dh->readLabelData("../train-labels-idx1-ubyte");
    dh->countClasses();
    dh->splitData();
    
    KNN *nearest = new KNN();
    nearest->setK(3);
    nearest->setTrainingData(dh->getTrainingData());
    nearest->setTestData(dh->getTestData());
    nearest->setValidationData(dh->getValidationData());
    double performance = 0;
    double best_performance = 0;
    int best_k = 1;
    for(int i = 1; i <= 3; i++)
    {
        if(i == 1)
        {
            performance = nearest->validatePerformance();
            best_performance = performance;
        } else
        {
            nearest->setK(i);
            performance = nearest->validatePerformance();
            if(performance > best_performance)
            {
                best_performance = performance;
                best_k = i;
            }


        }
    }
    nearest->setK(best_k);
    nearest-> testPerformance();
}