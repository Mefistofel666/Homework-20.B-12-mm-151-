#ifndef KNN_H
#define KNN_H

#include "common.h"
#include "result.h"

// class result
// {
// private:
//     int trainSize;
//     double time;
//     double performance;

//     // int k; // количество соседей
//     // int layersCount;// количество слоев нейросети
// public:
//     result(int trainSize_, double time_, double perf): trainSize(trainSize_), time(time_), performance(perf){}
//     int getTrainSize();
//     double getTime();
//     double getPerformance();
// };


class KNN : public CommonData
{
    int k; // количество соседей
    std::vector<Data *> *neighbours; // соседи...
    std::vector<result> results;

public:
    KNN(int k);
    KNN();
    ~KNN();

    void findKnearest(Data *queryPoint); // поиск к-ближайших
    void setK(int val); // установка нового числа соседей
    int findMostFrequentClass(); // поиск самого часто встречающегося класса

    std::vector<result> getResults();

    int predict(); // предсказание класса
    double calculateDistance(Data *queryPoint, Data *input); // евклидово, манхэттенское, расстояние Чебышева
    // тестовая часть
    double validatePerformance();
    double testPerformance();



};




#endif