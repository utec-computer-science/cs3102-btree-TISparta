#include <vector>
#include <iostream>

template <typename T>
class Traits {
public:
  using value_t = T;
  using container_t = std::vector <value_t>;
  using iterator_t = typename container_t::iterator;

  class SimpleSearch {
  public:
    int operator () (container_t a, value_t v) {
      return 0;
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
