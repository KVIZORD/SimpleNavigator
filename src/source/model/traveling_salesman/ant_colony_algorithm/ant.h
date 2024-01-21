#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_ANT_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_ANT_H_

#include <random>
#include <vector>

#include "model/s21_graph.h"
#include "model/traveling_salesman/common/path_structure.h"
#include "pheromone.h"

namespace s21 {

class Ant {
 public:
  const double kAlpha = 1;
  const double kBetta = 1;
  const double kDistance = 1;

  Ant(Graph &distances, std::mt19937 &gen, double pheromon_quantiy);

  TsmResult &GetPath();
  double GetPheromonQuantiy() const ;
  bool Move(Pheromones &pheromones);

 private:
  Graph &distances_;
  std::mt19937 &gen_;
  double pheromon_quantiy_;
  std::vector<bool> used_vertex_;
  TsmResult path_{};

  size_t GetCurrentVertex();
  std::vector<double> GetProbabilities(const Pheromones &pheromones,
                                       std::vector<size_t> &neighbors);
  double GetRandomProbability();
  std::vector<size_t> GetVerticesPossibleNeighbors();
  double CalcSummaryWeight(const Pheromones &pheromones,
                           std::vector<size_t> &neighbors);
};

};  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_ANT_H_