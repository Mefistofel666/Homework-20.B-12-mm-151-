#include "bayes.h"
#include "data_handler.h"
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
        prob[i] = (double)summariesByClass[i][0].count / totalRows;
        for(int j = 0; j < summariesByClass[i].size(); j++)
        {
            double mean = summariesByClass[i][j].mean;
            double sd = summariesByClass[i][j].sd;
            int count  = summariesByClass[i][j].count;

            prob[i] *= calcProb(row[j], mean, sd);
        }
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
void NaiveBayes::test()
{
    int count = 0;
    int index = 0;
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
        std::cout << "Current Accuracy: " << 100*(double)count/(double)(index) << "%.\n";

    }
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


int main()
{
    DataHandler *data_handler = new DataHandler();
    data_handler->readCsv("../iris.txt", ",");
    data_handler->splitData();
    NaiveBayes *bayes = new NaiveBayes();

    bayes->setTrainingData(data_handler->getTrainingData());
    bayes->setTestData(data_handler->getTestData());
    bayes->setValidationData(data_handler->getValidationData());

    bayes->separateByClass(); 
    bayes->summarizingDataset(); 
    bayes->summarizingByClass(); 
    // printSumByClass(bayes->getSummariesByClass());
    // std::vector<double> test {5.4,3.9,1.7,.4};
    // int res = bayes->predict(test);
    // std::cout << "prediction -> " << res << " Expected -> 0\n";
    // printProb(bayes->getProb());
    
    
    bayes->test();

    std::cout << "\n";
    std::cout << "[Setosa] -> 0; \n[Versicolor] -> 1; \n[Virginica] -> 2\n";



    // Test Gaussian
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