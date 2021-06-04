#include "data_handler.h"
#include <random>
#include <algorithm>
#include <iostream>

// конструктор
// определяем основные поля для работы с данными
DataHandler::DataHandler()
{
    dataArray = new std::vector<Data *>;
    trainingData = new std::vector<Data *>;
    testData = new std::vector<Data *>;
    validationData = new std::vector<Data *>;
}

// Да.
DataHandler::~DataHandler()
{
    // fix me!!!
}

// Чтение данных в CSV формате, то есть данные записаны через ", " / "," / любой другой разделитель
void DataHandler::readCsv(std::string path, std::string delimiter)
{
    classCounts = 0;   
    std::ifstream data_file;
    data_file.open(path.c_str());
    std::string line;

    while(std::getline(data_file, line)) // построчно считываем данные 
    {
        if(line.length() == 0) continue;
        Data *d = new Data();
        d->setNormalizedFeatureVector(new std::vector<double>());
        size_t position = 0;
        std::string token;
        while((position = line.find(delimiter)) != std::string::npos) // пока разделитель найден
        {
            token = line.substr(0, position);
            d->appendToFeatureVector(std::stod(token));
            line.erase(0, position + delimiter.length());
        }
        if(classFromString.find(line) != classFromString.end()) // класс не уникален, т.е. уже содержится в classFromString
        {
            d->setLabel((uint8_t)classFromString[line]);
        }else // найден новый уникальный класс
        {
            classFromString[line] = classCounts;
            std:: cout << "line: " << line << " , class:" << classCounts << "\n"; // присваиваем этому новому классу идущий по порядку номер
            d->setLabel((uint8_t)classFromString[line]);
            classCounts++;
        }
        dataArray->push_back(d);
    }
    for(Data *data : *dataArray)
        data->setClassVector(classCounts);
    featureVectorSize = dataArray->at(0)->getNormalizedFeatureVector()->size();
}

// Чтение данных MNIST
void DataHandler::readInputData(std::string path)
{
    uint32_t magic = 0;
    uint32_t num_images = 0; // кол-во изображений
    uint32_t num_rows = 0; // количество строк
    uint32_t num_cols = 0; // кол-во колонок
    unsigned char bytes[4]; // параметры описанные выше по 32 бита
    FILE *f = fopen(path.c_str(), "rb");
    if (f)
    {
        // считываем информацию о данных
        int i = 0;
        while(i < 4)
        {
            // из потока f в переменную bytes считываем 1 штуку размера 4 байт = 32 бита
            if(fread(bytes,sizeof(bytes), 1,f)) 
            {
                switch(i)
                {
                    case 0:
                        magic = format(bytes);
                        i++;
                        break;
                    case 1:
                        num_images = format(bytes);
                        i++;
                        break;
                    case 2:
                        num_rows = format(bytes);
                        i++;
                        break;
                    case 3:
                        num_cols = format(bytes);
                        i++;
                        break;
                }
            }
        }
        printf("Done getting file header.\n");

        uint32_t image_size = num_rows * num_cols; // логично. Тут 24 * 24 = 784
        // каждая фотка это экземпляр класса Data 
        for (int i = 0; i < num_images; i++)
        {
            Data *d = new Data();
            d->setFeatureVector(new std::vector<uint8_t>());
            uint8_t element[1]; // один пиксель = 8 бит =  1 байт
            for (int j = 0; j < image_size; j++)
            {
                // в element из потока f считываем 1 байт
                if (fread(element, sizeof(element), 1, f))
                {
                    d->appendToFeatureVector(element[0]);   

                }
                else
                {
                    printf("Error reading from file.\n");
                    exit(1);
                }
            }
            dataArray->push_back(d);
            dataArray->back()->setClassVector(classCounts);
        }
        normalize();
        featureVectorSize = dataArray->at(0)->getFeatureVector()->size();
        printf("Succesfully read and stored %lu data entries.\n", dataArray->size());
        printf("The Feature Vector Size is: %d\n", featureVectorSize);
    }
    else
    {
        printf("Could not find file.\n");
        exit(1);
    }
}
void DataHandler::readLabelData(std::string path)
{
    // почти тоже самое что и для входных данных
    uint32_t magic = 0;
    uint32_t num_images = 0;
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "rb");
    if (f)
    {
        int i = 0;
        while(i < 2)
        {
            if(fread(bytes, sizeof(bytes), 1,f))
            {
                switch (i)
                {
                case 0:
                    magic = format(bytes);
                    i++;
                    break;
                
                case 1:
                    num_images = format(bytes);
                    i++;
                    break;
                }
            }
        }
        for (unsigned j = 0; j < num_images; j++)
        {
            uint8_t element[1];
            if (fread(element, sizeof(element), 1, f))
            {
                dataArray->at(j)->setLabel(element[0]); // устанавливаем метку соответствующей картинке

            }
            else
            {
                printf("Error reading from file.\n");
                exit(1);
            }
        }
        printf("Done getting Label File Header.\n");
    }
    else
    {
        printf("Could not find file.\n");
        exit(1);
    }
}
// разбиение данных
void DataHandler::splitData()
{
    std::unordered_set<int> used_indexes; 
    int train_size = dataArray->size() * TRAIN_SET_PERCENT;
    int test_size = dataArray->size() * TEST_SET_PERCENT;
    int valid_size = dataArray->size() * VALIDATATION_PERCENT;

    std::random_shuffle(dataArray->begin(), dataArray->end()); // перемешиваем данные

    // Training data
    int count = 0;
    int index = 0;
    while (count < train_size)
    {
        trainingData->push_back(dataArray->at(index++));
        count++;
    }
    // Test Data
    count = 0;
    while (count < test_size)
    {
        testData->push_back(dataArray->at(index++));
        count++;
    }

    // Validation Data
    count = 0;
    while (count < valid_size)
    {
        validationData->push_back(dataArray->at(index++));
        count++;
    }
    printf("Training Data Size: %lu.\n", trainingData->size());
    printf("Test Data Size: %lu.\n", testData->size());
    printf("Validation Data Size: %lu.\n", validationData->size());
}
// подсчет количества классов для MNIST
void DataHandler::countClasses()
{
    int count = 0;
    for (unsigned i = 0; i < dataArray->size(); i++)
    {
        if (classFromInt.find(dataArray->at(i)->getLabel()) == classFromInt.end())
        {
            classFromInt[dataArray->at(i)->getLabel()] = count;
            // dataArray->at(i)->setEnumeratedLabel(count); // можно убрать
            count++;
        }
        else
        {
            // dataArray->at(i)->setEnumeratedLabel(classFromInt[dataArray->at(i)->getLabel()]);
        }
    }
    classCounts = count;
    for(Data *data : *dataArray)
    {
        data->setClassVector(classCounts);
    }
    printf("Succesfully Extracted %d Unique Classes.\n", classCounts);
}

// convert to little endian
uint32_t DataHandler::format(const unsigned char *bytes)
{
    // в 32 битах 4 байта. big endiand: A3, A2, A1, A0 -> little endian: A0, A1, A2, A3
    return (uint32_t)((bytes[0] << 24) | // A3->A0
                      bytes[1] << 16 | // A2->A1
                      bytes[2] << 8 | // A1->A2
                      bytes[3]); // A0 -> A3
}

// нормализация по методу минимакс(для фоточек самое то): преобразуем исходный набор в отрезок [0,1]
// можно реализовать Z-нормализацию
// X_n = (X_i - X_min) / (X_max - X_min)
void DataHandler::normalize()
{
    std::vector<double> mins, maxs;
    // инициализируем векторы мин и макс на первом экземпляре
    Data *d = dataArray->at(0);
    for(auto val : *d->getFeatureVector())
    {
        mins.push_back(val);
        maxs.push_back(val);
    }
    for(int i = 1; i < dataArray->size(); i++)
    {
        d = dataArray->at(i);
        for(int j = 0; j < d->getFeatureVectorSize(); j++)
        {
            double value = (double)d->getFeatureVector()->at(j);
            if(value < mins.at(j)) mins[j] = value;
            if(value > maxs.at(j)) maxs[j] = value;
        }
    }

    for(int i = 0; i < dataArray->size(); i++)
    {
        dataArray->at(i)->setNormalizedFeatureVector(new std::vector<double>());
        dataArray->at(i)->setClassVector(classCounts);
        for(int j = 0; j < dataArray->at(i)->getFeatureVectorSize(); j++)
        {
            if(maxs[j] - mins[j] == 0) dataArray->at(i)->appendToFeatureVector(0.0);
            else
            {
                dataArray->at(i)->appendToFeatureVector((double)(dataArray->at(i)->getFeatureVector()->at(j) - mins[j])/(maxs[j]-mins[j]));
            }
        } 

    }
}
// ну тут все понятно, просто геттеры
int DataHandler::getDataArraySize()
{
    return dataArray->size();
}
int DataHandler::getTrainingDataSize()
{
    return trainingData->size();
}
int DataHandler::getTestDataSize()
{
    return testData->size();
}
int DataHandler::getValidationSize()
{
    return validationData->size();
}

int DataHandler::getClassCounts()
{
    return classCounts;
}

std::vector<Data *> *DataHandler::getTrainingData()
{
    return trainingData;
}
std::vector<Data *> *DataHandler::getTestData()
{
    return testData;
}

std::vector<Data *> *DataHandler::getValidationData()
{
    return validationData;
}
std::map<uint8_t, int> DataHandler::getClassMap()
{
    return classFromInt;
}
std::map<std::string, int> DataHandler::getClassFromString()
{
    return classFromString;
}

void DataHandler::print()
{
    printf("Training Data:\n");
    for(auto data :*trainingData)
    {
        for(auto value : *data->getNormalizedFeatureVector())
        {
            printf(".3f, ", value);
        }
        printf(" -> %d", data->getLabel());
    }
    return;

    printf("Test Data:\n");
    for(auto data : *testData)
    {
        for(auto value : *data->getNormalizedFeatureVector())
        {
            printf("%.3f, ", value);
        }
        printf(" ->   %d\n", data->getLabel());
    }

    printf("Validation Data:\n");
    for(auto data : *validationData)
    {
        for(auto value : *data->getNormalizedFeatureVector())
        {
            printf("%.3f, ", value);
        }
        printf(" ->   %d\n", data->getLabel());
    }
}

// int main()
// {

//     data_handler *dh = new data_handler();
//     dh->read_feature_vector("train-images-idx3-ubyte");
//     dh->read_feature_labels("train-labels-idx1-ubyte");
//     dh->split_data();
//     dh->count_classes();
//     return 0;
// }