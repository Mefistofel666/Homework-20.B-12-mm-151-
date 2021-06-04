#ifndef KNN_H
#define KNN_H

#include "common.h"

class KNN:public CommonData
{
    int k; // количество соседей
    std::vector<Data *> *neighbours; // соседи...


public:
    KNN(int k);
    KNN();
    ~KNN();

    void findKnearest(Data *queryPoint); // поиск к-ближайших
    void setK(int val); // установка нового числа соседей
    int findMostFrequentClass(); // поиск самого часто встречающегося класса


    int predict(); // предсказание класса
    double calculateDistance(Data *queryPoint, Data *input); // евклидово, манхэттенское, расстояние Чебышева
    // тестовая часть
    double validatePerformance();
    double testPerformance();
};

#endif