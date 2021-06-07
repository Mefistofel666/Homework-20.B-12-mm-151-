#ifndef __KMEANS_HPP
#define __KMEANS_HPP
#include "common.h"
#include <unordered_set>
#include <limits>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <map>
#include "data_handler.h"
#include "result.h"
typedef struct cluster 
{
  std::vector<double> *centroid; // центр масс класстера  = ср. арифметическое
  std::vector<Data *> *clusterPoints; // точки принадлежащие этому кластеру
  std::map<int, int> classCounts; // количество классов в кластере
  int mostFrequentClass; // самый популярный класс в кластере
  cluster(Data *initialPoint) // конструктор
  {
      centroid = new std::vector<double>;
      clusterPoints = new std::vector<Data *>;
      for(auto val : *(initialPoint->getNormalizedFeatureVector()))
      {
          if(isnan(val))
            centroid->push_back(0);
          else
            centroid->push_back(val);
      }
      clusterPoints->push_back(initialPoint);
      classCounts[initialPoint->getLabel()] = 1;
      mostFrequentClass = initialPoint->getLabel();
  }
 
  void add_to_cluster(Data* point)
  {
    int previous_size = clusterPoints->size();
    clusterPoints->push_back(point);
    // вместо прохода по всем точкам кластера можно вычислить новый центроид на основе старого
    for(int i = 0; i < centroid->size() - 1; i++)
    {
        double val = centroid->at(i);
        // умножили среднее арифм. на количство и получили сумму, теперь надо добавить только новое значение 
        // и разделить на новое количество
        val *= previous_size; 
        val += point->getNormalizedFeatureVector()->at(i);
        val /= (double)clusterPoints->size();
        centroid->at(i) = val;
    }
    if(classCounts.find(point->getLabel()) == classCounts.end())
    {
        classCounts[point->getLabel()] = 1;
    } else
    {
        classCounts[point->getLabel()]++;
    }
    set_mostFrequentClass();
  }
  void set_mostFrequentClass()
  {
      int best_class;
      int freq = 0;
      for(auto kv : classCounts)
      {
        if(kv.second > freq)
        {
          freq = kv.second;
          best_class = kv.first;
        }
      }
      mostFrequentClass = best_class;
  }
} cluster_t;

class kmeans : public CommonData
{
  int numClusters; // количество класстеров
  std::vector<cluster_t *> *clusters; // вектор класстеров
  std::unordered_set<int> *usedIndexes; 
  public:
  kmeans(int k);
  void initClusters();
  void initClustersForEachClass();
  void train();
  double euclideanDistance(std::vector<double> *, Data *);
  double validate();
  double test();
  std::vector<cluster_t *> * getClusters();
};
#endif
