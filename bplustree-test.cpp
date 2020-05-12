#include <set>

#include <gtest/gtest.h>

#include "utility/Random.hpp"
#include "traits/Trait1.hpp"
#include "traits/Trait2.hpp"
#include "b_plus_tree/BPlusTree.hpp"

const int MIN_VAL = -1000;
const int MAX_VAL = +1000;

TEST (Trait_1, int_insert_and_find) {
  using value_t = int;
  using trait_t = Trait1 <value_t>;
  const int order = 33;
  BPlusTree <trait_t, order> tree;
  const int n_elements = 1000;
  std::vector <value_t> values(n_elements);
  std::set <value_t> used;
  for (auto& value: values) {
    value = Random::generate_value <value_t> (MIN_VAL, MAX_VAL);
    if (used.count(value)) {
      EXPECT_FALSE(tree.insert(value));
    } else {
      EXPECT_TRUE(tree.insert(value));
    }
    used.insert(value);
  }
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

TEST (Trait_1, long_long_insert_and_find) {
  using value_t = long long;
  using trait_t = Trait1 <value_t>;
  const int order = 42;
  BPlusTree <trait_t, order> tree;
  const int n_elements = 1000;
  std::vector <value_t> values(n_elements);
  std::set <value_t> used;
  for (auto& value: values) {
    value = Random::generate_value <value_t> (MIN_VAL, MAX_VAL);
    if (used.count(value)) {
      EXPECT_FALSE(tree.insert(value));
    } else {
      EXPECT_TRUE(tree.insert(value));
    }
    used.insert(value);
  }
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

TEST (Trait_1, char_insert_and_find) {
  using value_t = char;
  using trait_t = Trait1 <value_t>;
  const int order = 3;
  BPlusTree <trait_t, order> tree;
  const int n_elements = 1000;
  std::vector <value_t> values(n_elements);
  std::set <value_t> used;
  for (auto& value: values) {
    value = Random::generate_value <value_t> ();
    if (used.count(value)) {
      EXPECT_FALSE(tree.insert(value));
    } else {
      EXPECT_TRUE(tree.insert(value));
    }
    used.insert(value);
  }
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

TEST (Trait_2, int_insert_and_find) {
  using value_t = int;
  using trait_t = Trait2 <value_t>;
  const int order = 33;
  BPlusTree <trait_t, order> tree;
  const int n_elements = 1000;
  std::vector <value_t> values(n_elements);
  std::set <value_t> used;
  for (auto& value: values) {
    value = Random::generate_value <value_t> (MIN_VAL, MAX_VAL);
    if (used.count(value)) {
      EXPECT_FALSE(tree.insert(value));
    } else {
      EXPECT_TRUE(tree.insert(value));
    }
    used.insert(value);
  }
  for (auto& value: values) {
    EXPECT_TRUE(tree.find(value));
  }
}

TEST (print, trait_1) {
  using value_t = int;
  using trait_t = Trait1 <value_t>;
  const int order = 4;
  BPlusTree <trait_t, order> tree;
  const int n_elements = 20;
  for (int value = 1; value <= n_elements; value++) {
    tree.insert(value);
  }
  std::cout << tree;
}

TEST (print, trait_2) {
  using value_t = int;
  using trait_t = Trait2 <value_t>;
  const int order = 4;
  BPlusTree <trait_t, order> tree;
  const int n_elements = 20;
  for (int value = 1; value <= n_elements; value++) {
    tree.insert(value);
  }
  std::cout << tree;
}

int main (int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
