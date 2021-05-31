#ifndef BAYES_H
#define BAYES_H
#include "common.h"
#include <iostream>
#include <cmath>
#include <map>
#include <ostream>


// typedef struct class_summary
// {
//     std::vector<std::vector<double>> MeanStdev;
//     double classProb;

// } class_summary;


// class NaiveBayes : public CommonData
// {
// private:
//     std::vector<class_summary> summary;
//     std::vector<double> uniqueLabel;
// public:
//     void fit(); // training
//     int predict(); // predict

//     double mean(Data *d); // среднее арифметическое(мат. ожидание)  \ считаем что все значение равновероятны
//     double stDev(Data *d); // стандартное отклонение
//     double calcProb(double val,double mean,double stdev); // вычисление вероятности
//     class_summary calcClassSummary(std::vector<Data *> dataset);
    
// };

// нужно рассчитать вероятность каждого класса и вероятность того, что каждое значение может принадлежать этому классу
// будем использовать нормальное распределение для вычисления вероятности


// 5 шагов:
// 

struct summary
{
public:
    double mean;
    double sd;
    double count;
    summary():mean(0), sd(0), count(0){};
    friend std::ostream &operator<<(std::ostream &os, const summary &s);
};


class NaiveBayes : public CommonData
{
private:
     // separate by class
    std::map<int ,std::vector<Data *> > separated;
    std::vector<summary> summaries; // тройки (mean | sd | count)
    std::map<int,std::vector<summary>> summariesByClass;
    std::map<int, double> prob; // предсказанные вероятности
   
public:
    NaiveBayes();
    void separateByClass();
    void summarizingDataset(); // вычисление среднего, стандартного отклонения
    void summarizingByClass();
    double calcProb(double x, double mean, double sd);
    void calculateClassProb(std::vector<double> row);
    int bestLabel(std::vector<double> row);
    int predict(std::vector<double> row);
    void test();



    // getters
    std::map<int ,std::vector<Data *>> getSeparated();
    std::vector<summary> getSummaries();
    std::map<int, std::vector<summary>> getSummariesByClass();
    std::map<int,double> getProb();
};




#endif