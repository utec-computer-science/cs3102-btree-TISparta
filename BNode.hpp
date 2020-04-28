#include <vector>

template <typename Trait, int BTREE_ORDER>
class BNode {
public:
  using value_t = typename Trait::value_t;
  using container_t = typename Trait::container_t;
  using iterator_t = typename Trait::iterator_t;
  using node = BNode <Trait, BTREE_ORDER>;
  using child_container_t = std::vector <node*>;

  std::size_t count;
  container_t data;
  child_container_t children;

  enum state {
    BT_OVERFLOW,
    BT_UNDERFLOW,
    NORMAL
  };

  BNode () {
    count = 0;
    data.resize(BTREE_ORDER + 1);
    children.resize(BTREE_ORDER + 2, nullptr);
  }

  ~BNode () {
    for (auto child: children) {
      if (child) {
        delete child;
      }
    }
    children.clear();
  }

  void insert (std::size_t pos, const value_t& value) {
    int cur = count;
    while (cur > pos) {
      data[cur] = data[cur - 1];
      children[cur + 1] = children[cur];
      cur--;
    }
    data[cur] = value;
    children[cur + 1] = children[cur];
    count++;
  }

  inline bool is_overflow () {
    return count > BTREE_ORDER;
  }

  inline bool is_underflow () {
    return count < BTREE_ORDER / 2;
  }

};
