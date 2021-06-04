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
    //fix me
}

// O(KN), где N - размер тренировочной выборки, k - число соседей
// O(N^2) if K ~ N
// if K is small then O(N)
// можно найти расстояние до всех точек, после чего отсортировать и взять k первых => O(N * log N). при огромных k это кажется неплохая идея
// Тут же последовательно находятся k ближайших точек
void KNN::findKnearest(Data *queryPoint)
{
    neighbours = new std::vector<Data *>;
    double min = std::numeric_limits<double>::max(); 
    double previous_min = min;
    int index;
    for (int i = 0; i < k; i++)
    {
        if (i == 0) // инициализируем минимумы
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

// поиск самого часто встречающегося класса
int KNN::findMostFrequentClass()
{
    std::map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbours->size(); i++)
    {
        if (class_freq.find(neighbours->at(i)->getLabel()) == class_freq.end()) // если класс не найден, то устанавливаем 1
        {
            class_freq[neighbours->at(i)->getLabel()] = 1;
        }
        else // если класс уже был найден то увеличиваем это значение на 1
        {
            class_freq[neighbours->at(i)->getLabel()]++;
        }
    }

    // пробегаемся по только что созданному map и находим самый часто встречающийся
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
    return best; // предсказание модели
}
// расстояние в n-мерном пространстве
double KNN::calculateDistance(Data *queryPoint, Data *input)
{
    double distance = 0.0;
    if(queryPoint->getNormalizedFeatureVector()->size() != input->getNormalizedFeatureVector()->size())
    {
        printf("Vectors have different size.\n");
        exit(1);
    }
// евклидово расстояние - естественное обобщение расстояния между точками на плоскости или 3-мерным пространстве 
#ifdef EUCLID 
    for (unsigned i = 0; i < queryPoint->getNormalizedFeatureVector()->size(); i++)
    {
        distance += pow(queryPoint->getNormalizedFeatureVector()->at(i) - input->getNormalizedFeatureVector()->at(i), 2);
    }
    return sqrt(distance);
// расстояние городских кварталов. Двигаться можно только по "вертикалям" и "горизонаталям"(если говорить про плоскость)
// сумма длин проекций отрезка между точками на оси координат, если обобщить
#elif defined MANHATTAN
// PUT MANHATTAN IMPLEMENTATION HERE
    for(unsigned i = 0; i < queryPoint->getNormalizedFeatureVector()->size(); i++)
    {
        distance += abs(queryPoint->getNormalizedFeatureVector()->at(i) - input->getNormalizedFeatureVector()->at(i));
    }
    return distance;
// расстояние шахматной доски. Максимум модуля разности компонент векторов
#elif defined CHEBYSHEV
    double max_dist = -1.0;
    for(unsigned i = 0; i < queryPoint->getNormalizedFeatureVector()->size(); i++)
    {
        distance = abs(queryPoint->getNormalizedFeatureVector()->at(i) - input->getNormalizedFeatureVector()->at(i));
        if(distance > max)
        {
            max_dist = distance;
        }
    }
    return max_dist;

#endif
}

// просто тестирование
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
        // printf("Current Performance = %.3f %%\n",((double)count*100.0)/((double)data_index) );
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

    // написать для ирисов Фишера штучку
    DataHandler *dh = new DataHandler();
    #ifdef MNIST
        dh->readInputData("../train-images-idx3-ubyte");
        dh->readLabelData("../train-labels-idx1-ubyte");
        dh->countClasses();
    #else
        dh->readCsv("../iris.txt", ",");
    #endif

    dh->splitData();
    
    KNN *nearest = new KNN();
    nearest->setK(3);
    nearest->setTrainingData(dh->getTrainingData());
    nearest->setTestData(dh->getTestData());
    nearest->setValidationData(dh->getValidationData());
    double performance = 0;
    double best_performance = 0;
    int best_k = 1;
    std::vector<int> bests;
    for(int i = 1; i <= 80; i++) 
    {
        if(i == 1)
        {
            performance = nearest->validatePerformance();
            best_performance = performance;
        } else
        {
            nearest->setK(i);
            performance = nearest->validatePerformance();
            if(performance >= best_performance)
            {
                best_performance = performance;
                bests.push_back(i);
                best_k = i;
            }


        }
    }
    for(int i = 0; i < bests.size(); i++)
    {
        nearest->setK(bests[i]);
        printf("Best K = %i\n", bests[i]);
        nearest->testPerformance();
    }
    nearest->setK(4);
    printf("Best K = %i\n", 4);
    nearest->testPerformance();
    // k = 3 лучший параметр для MNIST
}