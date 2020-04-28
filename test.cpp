#include <gtest/gtest.h>

#include "Random.hpp"
#include "Traits.hpp"
#include "BTree.hpp"

const int MIN_VAL = -1000;
const int MAX_VAL = +1000;

TEST (B_Tree, int_insert_and_find) {
  using value_t = int;
  using trait_t = Traits <value_t>;
  const int order = 33;
  BTree <trait_t, order> tree;
  const int n_elements = 1000;
  std::vector <value_t> values(n_elements);
  for (auto& value: values) {
    value = Random::generate_value <value_t> (MIN_VAL, MAX_VAL);
    tree.insert(value);
  }
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

TEST (B_Tree, long_long_insert_and_find) {
  using value_t = long long;
  using trait_t = Traits <value_t>;
  const int order = 42;
  BTree <trait_t, order> tree;
  const int n_elements = 1000;
  std::vector <value_t> values(n_elements);
  int cnt = 0;
  for (auto& value: values) {
    value = Random::generate_value <value_t> (MIN_VAL, MAX_VAL);
    tree.insert(value);
  }
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

TEST (B_Tree, char_insert_and_find) {
  using value_t = char;
  using trait_t = Traits <value_t>;
  const int order = 3;
  BTree <trait_t, order> tree;
  const int n_elements = 1000;
  std::vector <value_t> values(n_elements);
  int cnt = 0;
  for (auto& value: values) {
    value = Random::generate_value <value_t> ();
    tree.insert(value);
  }
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

int main (int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
