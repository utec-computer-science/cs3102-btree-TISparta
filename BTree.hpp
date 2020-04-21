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
      split_root(root, value);
    }
  }

  bool find (const value_t& value) const {
    return find(root, value);
  }

private:
  node* root;

  int insert (node* pnode, const value_t& value) {
    std::size_t pos = 0;
    while (pos < pnode->count and pnode->data[pos] < value) {
      pos++;
    }
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

  void split (node* pnode, std::size_t pos) {
    node* node_in_overflow = pnode->children[pos];
    node* child_1 = node_in_overflow;
    child_1->count = 0;
    node* child_2 = new node();
    std::size_t iter = 0;
    std::size_t cur = 0;
    while (cur < BTREE_ORDER / 2) {
      child_1->children[cur] = node_in_overflow->children[iter];
      child_1->data[cur] = node_in_overflow->data[iter];
      child_1->count++;
      iter++;
      cur++;
    }
    child_1->children[cur] = node_in_overflow->children[iter];
    pnode->insert(pos, node_in_overflow->data[iter]);
    if (node_in_overflow->children[0]) {
      iter++;
    } else {
      child_2->right = child_1->right;
      child_1->right = child_2;
      pnode->children[pos + 1] = child_2;
    }
    cur = 0;
    while (iter < BTREE_ORDER + 1) {
      child_2->children[cur] = node_in_overflow->children[iter];
      child_2->data[cur] = node_in_overflow->data[iter];
      child_2->count++;
      iter++;
      cur++;
    }
    child_2->children[cur] = node_in_overflow->children[iter];
    pnode->children[pos] = child_1;
    pnode->children[pos + 1] = child_2;
  }

  void split_root (node* pnode, const value_t& value) {
    node* node_in_overflow = pnode;
    node* child_1 = new node();
    node* child_2 = new node();
    std::size_t iter = 0;
    std::size_t cur = 0;
    while (cur < BTREE_ORDER / 2) {
      child_1->children[cur] = node_in_overflow->children[iter];
      child_1->data[cur] = node_in_overflow->data[iter];
      child_1->count++;
      iter++;
      cur++;
    }
    child_1->children[cur] = node_in_overflow->children[iter];
    pnode->data[0] = node_in_overflow->data[iter];
    child_1->right = child_2;
    if (pnode->children[0]) {
      iter++;
    }
    cur = 0;
    while (iter < BTREE_ORDER + 1) {
      child_2->children[cur] = node_in_overflow->children[iter];
      child_2->data[cur] = node_in_overflow->data[iter];
      child_2->count++;
      iter++;
      cur++;
    }
    child_2->children[cur] = node_in_overflow->children[iter];
    pnode->children[0] = child_1;
    pnode->children[1] = child_2;
    pnode->count = 1;
  }

  bool find (node* pnode, const value_t& value) const {
    if (not pnode) {
      return false;
    }
    std::size_t cur = 0;
    while (cur < BTREE_ORDER + 1 and pnode->data[cur] < value) {
      cur++;
    }
    if (cur < BTREE_ORDER + 1 and pnode->data[cur] == value) {
      return true;
    }
    return find(pnode->children[cur], value);
  }

};
