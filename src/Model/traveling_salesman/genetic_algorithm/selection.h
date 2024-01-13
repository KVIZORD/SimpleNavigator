#ifndef SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_GENETIC_ALGORITHM_TSP_SELECTION_H
#define SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_GENETIC_ALGORITHM_TSP_SELECTION_H

#include <set>
#include <vector>

#include "../../s21_graph.h"
// #include "../common/path_structure.h"
#include "population.h"

namespace s21 {

class SelectionStrategy {
 public:
  virtual Population execute(Population &population) = 0;
};

class TournamentSelection : public SelectionStrategy {
 public:
  const size_t kParticipantCount = 3;

  Population execute(Population &population);

 private:
  std::random_device rd_{};
  std::mt19937 gen_{rd_()};

  std::set<size_t> generateUniqueRandomNumbers(size_t start, size_t end,
                                               size_t count);
  Chromosome getWinnerChromosome(Population &population,
                                 const std::set<size_t> &participant_indexes);
};

};  // namespace s21

#endif  // SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_GENETIC_ALGORITHM_TSP_SELECTION_H
