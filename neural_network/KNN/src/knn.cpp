#include "../include/knn.h"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"
#include "data_handler.h"

knn::knn(int val)
{
    k = val;
}
knn::knn()
{
    // Nothing to do
}
knn::~knn()
{
    //Nothing to do
}

// O(KN)
// O(N^2) if K ~ N
// if K is small then O(N)
// We can find distance for all data-points and sort them => O(N * log N) because array sorting is O(N * log N) and that is // good if K ~ N

void knn::find_knearest(data *query_point)
{
    neighbours = new std::vector<data *>;
    double min = std::numeric_limits<double>::max();
    double previous_min = min;
    int index = 0;
    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < training_data->size(); j++)
            {
                double distance = calculate_distance(query_point, training_data->at(j));
                training_data->at(j)->set_distance(distance);
                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbours->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
        else
        {
            for (int j = 0; j < training_data->size(); j++)
            {
                double distance = training_data->at(j)->get_distance();
                if (distance > previous_min && distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbours->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
    }
}

void knn::set_k(int val)
{
    k = val;
}

int knn::predict()
{
    std::map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbours->size(); i++)
    {
        if (class_freq.find(neighbours->at(i)->get_label()) == class_freq.end())
        {
            class_freq[neighbours->at(i)->get_label()] = 1;
        }
        else
        {
            class_freq[neighbours->at(i)->get_label()]++;
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
    neighbours->clear();
    return best;
}
double knn::calculate_distance(data *query_point, data *input)
{
    double distance = 0.0;
    if (query_point->get_feature_vector_size() != input->get_feature_vector_size())
    {
        printf("Error Vector Size Mismatch\n");
        exit(1);
    }

#ifdef EUCLID
    for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++)
    {
        distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
    }
    distance = sqrt(distance);
    return distance;

#elif defined MANHATTAN
// PUT MANHATTAN IMPLEMENTATION HERE
#endif

    
}
double knn::validate_performance()
{
    double current_performance = 0;
    int count = 0;
    int data_index = 0;
    for(data *query_point : *validation_data)
    {
        find_knearest(query_point);
        int prediction = predict();
        printf("%d -> %d \n", prediction, query_point->get_label());
        if(prediction == query_point->get_label())
        {
            count++;
        }
        data_index++;
        printf("Current Performance = %.3f %%\n",((double)count*100.0)/((double)data_index) );
    }
    current_performance =  ((double)count*100.0)/((double)validation_data->size());
    printf("Valifation Performance for K =%d : %.3f %%\n", k,current_performance);
    return current_performance;
}
double knn::test_performance()
{
    double current_performance = 0;
    int count = 0;
    for(data *query_point : *test_data)
    {
        find_knearest(query_point);
        int prediction = predict();
        if(prediction == query_point->get_label())
        {
            count++;
        }
    }
    current_performance = ((double)count*100.0)/((double(test_data->size())));
    printf("Tested Performance = %.3f %%\n", current_performance);
    return current_performance;
}

int main()
{
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../train-images-idx3-ubyte");
    dh->read_feature_labels("../train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();
    knn *knearest = new knn();
    knearest->set_training_data(dh->get_training_data());
    knearest->set_test_data(dh->get_test_data());
    knearest->set_validation_data(dh->get_validation_data());
    double performance = 0;
    double best_performance = 0;
    int best_k = 1;
    for(int i = 1; i <= 4; i++)
    {
        if(i == 1)
        {
            knearest->set_k(i);
            performance = knearest->validate_performance();
            best_performance = performance;
        } else
        {
            knearest->set_k(i);
            performance = knearest->validate_performance();
            if(performance > best_performance)
            {
                best_performance = performance;
                best_k = i;
            }


        }
    }
    knearest->set_k(best_k);
    knearest-> test_performance();
}