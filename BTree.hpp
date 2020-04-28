#include <vector>

#include "BNode.hpp"

template <typename Trait, int BTREE_ORDER>
class BTree {
public:
  using value_t = typename Trait::value_t;
  using container_t = typename Trait::container_t;
  using functor_t = typename Trait::functor_t;
  using print_t = typename Trait::print_t;
  using node = BNode <Trait, BTREE_ORDER>;

  BTree () {
    root = new node();
  }

  void insert (const value_t& value) {
    int state = insert(root, value);
    if (state == node::BT_OVERFLOW) {
      split(root, value, true);
    }
  }

  bool find (const value_t& value) const {
    return find(root, value);
  }

  void print (std::ostream& out) const {
    print_tree(root, 0, out);
  }

private:
  node* root;
  functor_t search;

  int insert (node* pnode, const value_t& value) {
    std::size_t pos = search(pnode->data, pnode->count, value);
    if (pnode->children[pos]) {
      int state = insert(pnode->children[pos], value);
      if (state == node::BT_OVERFLOW) {
        split(pnode, pos);
      }
    } else {
      pnode->insert(pos, value);
    }
    return pnode->is_overflow() ? node::BT_OVERFLOW : node::NORMAL;
  }

  void split (node* pnode, std::size_t pos, bool is_root = false) {
    node* poverflow = is_root ? pnode : pnode->children[pos];
    // left child
    node* child_1 = new node();
    std::move(std::begin(poverflow->data), 
              std::begin(poverflow->data) + BTREE_ORDER / 2, 
              std::begin(child_1->data));
    std::move(std::begin(poverflow->children), 
              std::begin(poverflow->children) + BTREE_ORDER / 2 + 1, 
              std::begin(child_1->children));
    child_1->count = BTREE_ORDER / 2;
    // right child
    node* child_2 = new node();
    std::move(std::begin(poverflow->data) + BTREE_ORDER / 2 + 1, 
              std::end(poverflow->data), 
              std::begin(child_2->data));
    std::move(std::begin(poverflow->children) + BTREE_ORDER / 2 + 1, 
              std::end(poverflow->children), 
              std::begin(child_2->children));
    child_2->count = BTREE_ORDER - BTREE_ORDER / 2;
    // updated node
    if (is_root) {
      pnode->data[0] = std::move(pnode->data[BTREE_ORDER / 2]);
      pnode->children[0] = child_1;
      pnode->children[1] = child_2;
      pnode->count = 1;
    } else {
      pnode->insert(pos, poverflow->data[BTREE_ORDER / 2]);
      pnode->children[pos] = child_1;
      pnode->children[pos + 1] = child_2;
    }
  }

  bool find (node* pnode, const value_t& value) const {
    if (not pnode) {
      return false;
    }
    std::size_t pos = search(pnode->data, pnode->count, value);
    if (pos < pnode->count and pnode->data[pos] == value) {
      return true;
    }
    return find(pnode->children[pos], value);
  }

  void print_tree (node* pnode, int level, std::ostream& out) const {
    std::size_t pos = 0;
    for (pos = pnode->count - 1; pos >= 0; pos--) {
      if (pnode->children[pos + 1]) {
        print(pnode->children[pos + 1], level + 1, out);
      }
      out << std::string(level * 2, ' ') << pnode->data[pos] << '\n';
    }
    if (pnode->children[pos + 1]) {
      print(pnode->children[pos + 1], level + 1, out);
    }
  }

};
