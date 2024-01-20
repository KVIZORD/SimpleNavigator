#ifndef SIMPLE_NAVIGATOR_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CHROMOSOME_H
#define SIMPLE_NAVIGATOR_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CHROMOSOME_H

#include <cstddef>
#include <limits>
#include <vector>
#include <cmath>

#include "../../s21_graph.h"

namespace s21 {

struct Chromosome {
  std::vector<size_t> genes;
  double distance;

  void updateDistance(Graph &distances) {
    if (genes.size() < 2) {
      throw std::invalid_argument("Chromosome size < 2");
    }

    distance = 0;

    for (size_t i = 0; i < genes.size() - 1; ++i) {
      if (genes[i] != genes[i + 1] &&
          distances.GetValue(genes[i], genes[i + 1]) == 0) {
        distance = std::numeric_limits<double>::infinity();
        break;
      };
      distance += distances.GetValue(genes[i], genes[i + 1]);
    }
    // if (!std::isinf(distance)) {
    //   for (auto &el : genes) {
    //     std::cout << el << " ";
    //   }
    //   std::cout << std::endl;
    //   std::cout << "Chromosome distance: " << distance << std::endl;
    // }
  }
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CHROMOSOME_H
