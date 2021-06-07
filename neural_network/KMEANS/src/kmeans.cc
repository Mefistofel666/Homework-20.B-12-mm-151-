#include "../include/kmeans.h"
#include <chrono>
#include <fstream>

kmeans::kmeans(int k)
{
    numClusters = k;
    clusters = new std::vector<cluster_t *>;
    usedIndexes = new std::unordered_set<int>;
}

void kmeans::initClusters()
{
  for(int i = 0; i < numClusters; i++)
  {
    int index = (rand() % trainingData->size());
    while(usedIndexes->find(index) != usedIndexes->end())
    {
      index = (rand() % trainingData->size());
    }
    clusters->push_back(new cluster_t(trainingData->at(index)));
    usedIndexes->insert(index);
  }
}

void kmeans::initClustersForEachClass()
{
  std::unordered_set<int> classes_used;
  for(int i = 0; i < trainingData->size(); i++)
  {
    if(classes_used.find(trainingData->at(i)->getLabel()) == classes_used.end())
    {
      clusters->push_back(new cluster_t(trainingData->at(i)));
      classes_used.insert(trainingData->at(i)->getLabel());
      usedIndexes->insert(i);
    }
  }
}
void kmeans::train()
{
  while(usedIndexes->size() < trainingData->size())
  {
    int index = (rand() % trainingData->size());
    while(usedIndexes->find(index) != usedIndexes->end())
    {
      index = (rand() % trainingData->size());
    }
    double min_dist = std::numeric_limits<double>::max();
    int best_cluster = 0;
    for(int j = 0; j < clusters->size(); j++)
    {
      double dist = euclideanDistance(clusters->at(j)->centroid, trainingData->at(index));
      if(dist < min_dist)
      {
        min_dist = dist;
        best_cluster = j;
      }
    }
    clusters->at(best_cluster)->add_to_cluster(trainingData->at(index));
    usedIndexes->insert(index);
  }
}

double kmeans::euclideanDistance(std::vector<double> * centroid, Data *query_point)
{
  double dist = 0.0;
  for(int i = 0; i < centroid->size(); i++)
  {
    dist += pow(centroid->at(i) - query_point->getNormalizedFeatureVector()->at(i), 2);
  }
  return sqrt(dist);
}
double kmeans::validate()
{
  double num_correct = 0.0;
  for(auto query_point : *validationData)
  {
    double min_dist = std::numeric_limits<double>::max();
    int best = 0;
    for(int i = 0; i < clusters->size(); i++)
    {
      double current_dist = euclideanDistance(clusters->at(i)->centroid, query_point);
      if(current_dist < min_dist)
      {
        min_dist = current_dist;
        best = i;
      }
    }
    if(clusters->at(best)->mostFrequentClass == query_point->getLabel()) num_correct++;
  }
  return 100.0 * (num_correct / (double) validationData->size());
}
double kmeans::test()
{
  double num_correct = 0.0;
  for(auto query_point : *testData)
  {
    double min_dist = std::numeric_limits<double>::max();
    int best = 0;
    for(int i = 0; i < clusters->size(); i++)
    {
      double current_dist = euclideanDistance(clusters->at(i)->centroid, query_point);
      if(current_dist < min_dist)
      {
        min_dist = current_dist;
        best = i;
      }
    }
    if(clusters->at(best)->mostFrequentClass == query_point->getLabel()) num_correct++;
  }
  return 100.0 * (num_correct / (double) testData->size());
}

std::vector<cluster_t *> * kmeans::getClusters()
{
  return this->clusters;
}

std::vector<result> getRes( DataHandler *dh)
{
    std::vector<result> *res = new std::vector<result>();
    std::vector<double> percents; // типа возможные размеры тренировочной выборки
    for(double i = 1.0; i < 8; i += 2)
    {
        percents.push_back(i / 10.0);
    }
    for(int i = 0; i < percents.size(); i++)
    {
        dh->splitData(percents[i], 0.0, 0.3); // (double)3/600 for mnist =  300; 0.3 for iris = 45
        int trainSize = percents[i] * dh->getDataArraySize();
        double time = 0;
        auto begin = std::chrono::steady_clock::now();
        // засекаем время
        double performance = 0;
        double best_performance = 0;
        int best_k = 1;
        // int k = 300;
        for(int k = dh->getClassCounts(); k < dh->getTrainingData()->size(); k++)
        {
            kmeans *km = new kmeans(k);
            km->setTrainingData(dh->getTrainingData());
            km->setTestData(dh->getTestData());
            km->setValidationData(dh->getValidationData());
            km->initClusters();
            km->train();
            performance = km->validate();
            // printf("Current Perforamnce @ K = %d: %.2f\n", k, performance);
            if(performance > best_performance)
            {
              best_performance = performance;
              best_k = k;
            }
        }
        printf("For k = %i => %f\n", best_k, best_performance);
        // отсекаем время
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - begin;
        time = elapsed_seconds.count();
        result r(trainSize, time, best_performance);
        res->push_back(r);
    }
    return *res;
}


int
main()
{ 
  DataHandler *dh = new DataHandler();
  #ifdef MNIST
    dh->readInputData("../train-images-idx3-ubyte");
    dh->readLabelData("../train-labels-idx1-ubyte");
    dh->countClasses();
  #else
    dh->readCsv("../iris.txt", ",");
  #endif
  // dh->splitData(0.7, 0.05,0.25);
  // double performance = 0;
  // double best_performance = 0;
  // int best_k = 26; 

  std::vector<result> result =  getRes(dh);

  std::ofstream to_csv;
  to_csv.open("kmeans_mnist.csv");
  to_csv << "TrainSize,Time,Performance\n";
  for(int i = 0; i < result.size(); i++)
  {
    int size = result[i].getTrainSize();
    double time = result[i].getTime();
    double perf = result[i].getPerformance();
    to_csv << size << "," << time << "," << perf << "\n";
  }

  // std::vector<int> bests;

  // for(int k = dh->getClassCounts(); k < dh->getTrainingData()->size(); k++)
  // {
  //     kmeans *km = new kmeans(k);
  //     km->setTrainingData(dh->getTrainingData());
  //     km->setTestData(dh->getTestData());
  //     km->setValidationData(dh->getValidationData());
  //     km->initClusters();
  //     km->train();
  //     performance = km->validate();
  //     printf("Current Perforamnce @ K = %d: %.2f\n", k, performance);
  //     if(performance >= best_performance)
  //     {
  //       bests.push_back(k);
  //       best_performance = performance;
  //       if(performance > best_performance)
  //         best_k = k;
  //     }
  // }

  // kmeans *km = new kmeans(best_k);
  // km->setTrainingData(dh->getTrainingData());
  // km->setTestData(dh->getTestData());
  // km->setValidationData(dh->getValidationData());
  // km->initClusters();
  // km->train();
  // printf("Best K = %i\n", best_k);
  // printf("Overall Performance: %.2f\n",km->test());


// 100 => 84.94; 200 => 87.24; 300 => 90.21 (13 min); 400 => 91.08 (17 min); 484 => 91.27( 20 min);  для MNIST
}

