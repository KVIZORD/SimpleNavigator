#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_MUTATION_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_MUTATION_H_

#include <random>

#include "population.h"

namespace s21 {

class MutationStrategy {
 public:
  virtual void execute(Population &population, double probability_mutation) = 0;
};

class ExchangeMutation : public MutationStrategy {
 public:
  void execute(Population &population, double probability_mutation = 0.01);

 private:
  std::random_device rd_{};
  std::mt19937 gen_{rd_()};

  void mutation(Chromosome &chromosome);
};

};  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_MUTATION_H_