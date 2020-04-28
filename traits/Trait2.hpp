#pragma once

#include <vector>
#include <iostream>

template <typename T>
class Trait2 {
public:
  using value_t = T;
  using container_t = std::vector <value_t>;
  using iterator_t = typename container_t::iterator;

  class SimpleSearch {
  public:
    std::size_t operator () (const container_t& data, std::size_t count, const value_t& value) const {
      std::size_t cur = 0;
      while (cur < count and data[cur] < value) {
        cur++;
      }
      return cur;
    }
  };

  class PostOrderPrint {
  public:
    void operator () (void) {
      std::cout << "post order" << std::endl;
    }
  };

  using functor_t = SimpleSearch;
  using print_t = PostOrderPrint;
};
