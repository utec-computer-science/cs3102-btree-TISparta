#include <gtest/gtest.h>

#include "Random.hpp"
#include "Traits.hpp"
#include "BTree.hpp"

const int MIN_VAL = -100;
const int MAX_VAL = +100;

TEST (B_Tree, int_insert_and_find) {
  using trait_t = Traits <int>;
  const int order = 3;
  BTree <trait_t, order> tree;
  const int n_elements = 100;
  for (int i = 0; i < n_elements; i++) {
    int value = Random::generate_value <int> (MIN_VAL, MAX_VAL);
    tree.insert(value);
  }
}

TEST (B_Tree, long_long_insert_and_find) {
  using trait_t = Traits <long long>;
  const int order = 5;
  BTree <trait_t, order> tree;
  const int n_elements = 100;
  for (int i = 0; i < n_elements; i++) {
    int value = Random::generate_value <long long> (MIN_VAL, MAX_VAL);
    tree.insert(value);
  }
}

int main (int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
