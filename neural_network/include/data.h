#ifndef DATA_H
#define DATA_H

#include <vector>
#include <stdint.h> // все ради uint8_t и проч. Чтобы быть уверенным в том, что на любой машине данные прочтутся правильно
#include <stdio.h>

class Data
{
    std::vector<uint8_t> *featureVector; // no class 
    std::vector<double> *normalizedFeatureVector; // вектор с нормализованными значениями (в данном случае минимакс нормализация)
    std::vector<int> *classVector; // 1 если i == label, а все остальные значения нули
    uint8_t label; // класс который ожидается в результате работы, т.е. реальный 
    // uint8_t enumeratedLabel; не надо
    double distance; // нужно для K-Means

public:
    // Data();
    // ~Data();

    void appendToFeatureVector(uint8_t); // для хитро-хрянищхся данных типа MNIST
    void appendToFeatureVector(double);  // CSV и прочее

    void printVector();
    void printNormalizedVector();

    // Setters
    void setFeatureVector(std::vector<uint8_t> *vec);
    void setNormalizedFeatureVector(std::vector<double> *vec);
    void setClassVector(int counts);
    void setLabel(uint8_t val);
    void setLabel(int val);
    void setEnumeratedLabel(uint8_t val);
    void setDistance(double val);

    // Getters
    int getFeatureVectorSize();
    double getDistance();
    uint8_t getLabel();
    uint8_t getEnumeratedLabel();
    std::vector<uint8_t> * getFeatureVector();
    std::vector<double> * getNormalizedFeatureVector();
    std::vector<int> getClassVector();

};

#endif