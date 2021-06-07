#include "bayes.h"
#include "data_handler.h"
#include "result.h"
#include <chrono>

void NaiveBayes::summarizingDataset()
{
    int size = trainingData->size();
    for(int i = 0; i < trainingData->at(0)->getNormalizedFeatureVector()->size(); i++)
    {
        summary *tmp = new summary();
        for(int j = 0; j < size; j++)
        {
            double mean = 0.0;
            double sd = 0.0;
            tmp->mean += trainingData->at(j)->getNormalizedFeatureVector()->at(i) / size;
        }

        for(int j = 0; j < size; j++)
        {
            tmp->sd += pow((trainingData->at(j)->getNormalizedFeatureVector()->at(i) - tmp->mean), 2) / (size - 1);
        }
        tmp->sd = sqrt(tmp->sd);
        tmp->count = size;
        summaries.push_back(*tmp);
    }
}

void NaiveBayes::summarizingByClass()
{
    for(int k = 0; k < separated.size(); k++) // проходим по каждому классу
    {
        for(int i = 0; i < trainingData->at(0)->getNormalizedFeatureVector()->size(); i++) //считаем параметры в каждом столбце
        {
            summary *tmp = new summary();
            for(int j = 0; j < separated[k].size(); j++)
            {
                tmp->mean += separated[k][j]->getNormalizedFeatureVector()->at(i) / separated[k].size();
            }

            for(int j = 0; j < separated[k].size(); j++)
            {
                tmp->sd += pow( (separated[k][j]->getNormalizedFeatureVector()->at(i) - tmp->mean), 2) / (separated[k].size() - 1);
            }
            tmp->sd = sqrt(tmp->sd);
            tmp->count = separated[k].size();
            summariesByClass[k].push_back(*tmp);
        } 
    }
}
void NaiveBayes::calculateClassProb(std::vector<double> row)
{
    int totalRows = 0.0;
    for(int i = 0; i < summariesByClass.size(); i++)
    {
        totalRows += summariesByClass[i][0].count;
    }

    for(int i = 0; i < summariesByClass.size(); i++)
    {
        prob[i] = (double)(summariesByClass[i][0].count + 1) / (totalRows + 10);
        for(int j = 0; j < summariesByClass[i].size(); j++)
        {
            double mean = summariesByClass[i][j].mean;
            double sd = summariesByClass[i][j].sd;
            if(sd == 0) sd = 1;
            int count  = summariesByClass[i][j].count;
            // std::cout << "mean = " << mean << "; sd = " << sd << "\n";

            prob[i] *= calcProb(row[j], mean, sd);
            // std:: cout <<  "calc prob = " << calcProb(row[j], mean, sd) << "\n";
        }
        // std::cout << "prob[i] = " << prob[i] << "\n";

    }
}
void printProb(std::map<int, double> prob)
{
    for(int i = 0; i < prob.size(); i++)
    {
        std::cout << i << " -> "<<  prob[i] << "\n";
    }
}


int NaiveBayes::bestLabel(std::vector<double> row)
{
    int bestLabel = -1;
    double bestProb = -1.0;
    for(int i = 0; i < prob.size(); i++)
    {
        // printProb(prob);
        // std::cout << "prob[i] = " << prob[i] << "\n";
        if(bestLabel == -1 || prob[i] > bestProb)
        {
            bestProb = prob[i];
            bestLabel = i;
            // std::cout << "best prob = " << bestProb << "\n";
            // std::cout << "best label = "<< bestLabel << "\n";
        }
    }
    
    return bestLabel;
}

int NaiveBayes::predict(std::vector<double> row)
{
    calculateClassProb(row);
    int prediction = bestLabel(row);
    return prediction;
}
double NaiveBayes::test()
{
    int count = 0;
    int index = 0;
    double performance = 0.0;
    for(Data *d : *testData)
    {
        index++;
        int expectedLabel = (int)d->getLabel();
        int predictedLabel = predict(*(d->getNormalizedFeatureVector()));
        if(expectedLabel == predictedLabel)
        {
            count++;
            
        }
        std::cout << "prediction: " << predictedLabel << " -> Expected: " << expectedLabel << "\n";
        performance = 100*(double)count/(double)(index);
        std::cout << "Current Accuracy: " << performance << "%.\n";
    }
    return performance;
}



NaiveBayes::NaiveBayes(){}


// class -> all Data with label = class 
void NaiveBayes::separateByClass()
{  
    for(Data *d : *trainingData)
    {
        auto classValue = d->getLabel();       
        separated[classValue].push_back(d);
    }
}



std::map<int ,std::vector<Data *>> NaiveBayes::getSeparated()
{
    return separated;
}
std::vector<summary> NaiveBayes::getSummaries()
{
    return summaries;
}

std::map<int ,std::vector<summary>> NaiveBayes::getSummariesByClass()
{
    return summariesByClass;
}

std::map<int, double> NaiveBayes::getProb()
{
    return prob;
}

std::ostream& operator<<(std::ostream &os, const summary &s)
{
    os << "(" << s.mean << ", " << s.sd << ", " << s.count << ")\n";
    return os;
}

double NaiveBayes::calcProb(double x, double mean, double sd)
{
    double exponent = exp( - ( pow(x - mean, 2)) / (2*sd*sd) );
    return (1/(sqrt(2*M_PI) * sd)) * exponent;
}


void printSumByClass(std::map<int, std::vector<summary>> m)
{
    for(int i = 0; i < m.size(); i++)
    {
        std::cout << i << "\n";
        for(int j = 0; j < m[i].size(); j++)
        {
            std::cout << m[i][j];
        }
    }
}

std::vector<result> getRes(DataHandler *dh)
{
    std::vector<result> *res = new std::vector<result>();
    std::vector<double> percents; // типа возможные размеры тренировочной выборки
    for(double i = 1.0; i < 8; i += 2)
    {
        percents.push_back(i / 10.0);
    }
    for(int i = 0; i < percents.size(); i++)
    {
        dh->splitData(percents[i], 0.3, 0); // (double)1/600 for mnist =  100; 0.3 for iris = 45
        int trainSize = percents[i] * dh->getDataArraySize();
        double time = 0;
        auto begin = std::chrono::steady_clock::now();
        // засекаем время
        NaiveBayes *bayes = new NaiveBayes();
        bayes->setTrainingData(dh->getTrainingData());
        bayes->setTestData(dh->getTestData());
        bayes->setValidationData(dh->getValidationData());
        bayes->separateByClass(); 
        bayes->summarizingDataset(); 
        bayes->summarizingByClass();
        double performance = bayes->test();
        printProb(bayes->getProb());
        // отсекаем время
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - begin;
        time = elapsed_seconds.count();
        result r(trainSize, time, performance);
        res->push_back(r);
    }
    return *res;
}



int main()
{
    DataHandler *data_handler = new DataHandler();
    #ifdef MNIST
        data_handler->readInputData("../train-images-idx3-ubyte");
        data_handler->readLabelData("../train-labels-idx1-ubyte");
        data_handler->countClasses();
    #else
        data_handler->readCsv("../iris.txt", ",");
    #endif
    // data_handler->splitData();
    // NaiveBayes *bayes = new NaiveBayes();

    // bayes->setTrainingData(data_handler->getTrainingData());
    // bayes->setTestData(data_handler->getTestData());
    // bayes->setValidationData(data_handler->getValidationData());

    // bayes->separateByClass(); 
    // bayes->summarizingDataset(); 
    // bayes->summarizingByClass(); 
    // printSumByClass(bayes->getSummariesByClass());
    // std::vector<double> test {5.4,3.9,1.7,.4};
    // int res = bayes->predict(test);
    // std::cout << "prediction -> " << res << " Expected -> 0\n";
    // printProb(bayes->getProb());
    
    // bayes->test();

    std::vector<result> results = getRes(data_handler);

    std::ofstream to_csv;
    to_csv.open("bayes_iris.csv");
    to_csv << "TrainSize,Time, Performance\n";
    for(int i = 0; i < results.size(); i++)
    {
        int size = results[i].getTrainSize();
        double time = results[i].getTime();
        double perf = results[i].getPerformance();
        to_csv << size << "," << time << "," << perf << "\n";
    }
    to_csv.close();

    // std::cout << "\n";
    // std:: map<std::string, int> classMap = data_handler->getClassFromString();
    // std:: cout << "[Setosa] -> "<< classMap["Iris-etosa"] << "\n";
    // std:: cout << "[Virginica] -> "<< classMap["Iris-virginica"] << "\n";
    // std:: cout << "[Versicolor] -> "<< classMap["Iris-versicolor"] << "\n";

    // Test Gaussssssssssssss
    // std::cout << bayes->calcProb(1.0,1.0,1.0);



    // Test summarizingByClass
    // bayes->summarizingByClass();
    // for(int i = 0; i < data_handler->getClassCounts(); i++)
    // {
    //     for(int j = 0; j < bayes->getSummariesByClass()[i].size(); j++)
    //     {
    //         std::cout << bayes->getSummariesByClass()[i][j];
    //     }
    // }

    // Test summarizing

    // bayes->summarizingDataset();
    // for(int i = 0; i < data_handler->getTrainingData()->at(0)->getNormalizedFeatureVector()->size(); i++)
    // {
    //     std::cout << bayes->getSummaries()[i];
    // }



    // Test separate
    // bayes->separateByClass();
    // std::vector<Data *> tmp1 = bayes->getSeparated()[0];
    // std::vector<Data *> tmp2 = bayes->getSeparated()[1];
    // std::vector<Data *> tmp3 = bayes->getSeparated()[2];

    // std::cout << "tmp1 size: " << tmp1.size() << "\n";
    // for(Data *d : tmp1)
    // {
    //     std::cout << (int)d->getLabel();
    // }
    // std::cout << "\ntmp2 size: " << tmp2.size() << "\n";

    // for(Data *d : tmp2)
    // {
    //     std::cout << (int)d->getLabel();
    // }
    // std::cout << "\ntmp3 size: " << tmp3.size() << "\n";

    // for(Data *d : tmp3)
    // {
    //     std::cout << (int)d->getLabel();
    // }

    


    return 0;
}