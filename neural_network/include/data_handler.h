#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <fstream>
#include "stdint.h"
#include "data.h"
#include <vector>
#include <string>
#include <map>  
#include <unordered_set> // Поиск, вставка и удаление O(1) в среднем.
#include <math.h> // sqrt

class DataHandler
{

    std::vector<Data *> * dataArray; // большой кусок данных до разбиения
    // разбили на тренировочную, тестовую и валидационную выборки
    std::vector<Data *> * trainingData; 
    std::vector<Data *> * testData;
    std::vector<Data *> * validationData;

    int classCounts; // количество классов в прочтенном датасете
    int featureVectorSize; // количество признаков(если говорить о признаковом описании)
    std::map<uint8_t, int> classFromInt; // классы соответствующие числам, т.е. класс = число изначально
    std::map<std::string, int> classFromString; // классы соответствующие текстовым данным, т.е. класс =  строке изначально

public:
    // хорошо бы принимать эти параметры при разбиении dataArray, но пока что лень
    //  указан процент от размера исходного датасета
    const double TRAIN_SET_PERCENT = 0.70;
    const double TEST_SET_PERCENT = 0.15;
    const double VALIDATATION_PERCENT = 0.15;


    DataHandler();
    ~DataHandler();

    // Чтение данных
    void readCsv(std::string, std::string);
    void readInputData(std::string path);
    void readLabelData(std::string path);

    // Обработка данных
    void splitData(); // разбиение исходных данных
    void countClasses(); // подсчет уникальных классов
    void normalize(); // нормализация (минимакс)
    void print();

    // Getters
    int getClassCounts();
    int getDataArraySize();
    int getTrainingDataSize();
    int getTestDataSize();
    int getValidationSize();
    std::vector<Data *> *getTrainingData();
    std::vector<Data *> *getTestData();
    std::vector<Data *> *getValidationData();
    std::map<uint8_t, int> getClassMap();
    std::map<std::string, int> getClassFromString();

    uint32_t format(const unsigned char *bytes); // convert to little endian

};

#endif