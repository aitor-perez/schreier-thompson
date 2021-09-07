// Tree.cpp
#include "Tree.h"

Tree* Tree::left() {
  return l;
}

Tree* Tree::right() {
  return r;
}

Tree* Tree::parent() {
  return p;
}

bool Tree::isLeaf() const {
  return (l == NULL) and (r == NULL);
}

bool Tree::isCaret(int n) {
  Tree* leaf = this->getLeaf(n);

  if (leaf == NULL) {
    return false;
  }

  Tree* parent = leaf->parent();

  if (parent == NULL or parent->left() != leaf) {
    return false;
  }

  if (parent->right() == NULL) {
    return false;
  }

  return parent->right()->isLeaf();
}

int Tree::leaves() {
  if (this->isLeaf()) {
    return 1;
  }

  return l->leaves() + r->leaves();
}

// Returns leaf number n
Tree* Tree::getLeaf(int n) {
  if (n < 1) {
    return NULL;
  }

  int leaves = this->leaves();

  if (n > leaves) {
    return NULL;
  }

  if (isLeaf()) {
    return this;
  }

  int leftLeaves = l->leaves();

  if (n <= leftLeaves) {
    return l->getLeaf(n);
  } else {
    return r->getLeaf(n - leftLeaves);
  }
}

// Returns number of leaf leaf
int Tree::findLeaf(Tree* leaf) {
  int n = this->leaves();

  for (int i=1; i<=n; i++) {
    if (this->getLeaf(i) == leaf) {
      return i;
    }
  }

  return 0;
}

// Adds a caret at leaf number n
void Tree::addCaret(int n) {
  Tree* leaf = this->getLeaf(n);

  if (leaf == NULL) {
    return;
  }

  leaf->l = new Tree();
  leaf->r = new Tree();

  leaf->l->p = leaf;
  leaf->r->p = leaf;
}

// Remove the caret formed by leaves n and n+1
void Tree::removeCaret(int n) {
  if (!this->isCaret(n)) {
    return;
  }

  Tree* root = this->getLeaf(n)->parent();

  delete root->left();
  delete root->right();

  root->l = NULL;
  root->r = NULL;
}

string Tree::toString(int offset) const {
  if (this->isLeaf()) {
    int leaf = offset + 1;
    return to_string(leaf);
  }

  int m = l->leaves();

  return "(" + l->toString(offset) + "-" + r->toString(offset + m) + ")";
}

ostream &operator<<(ostream &os, Tree const &t) {
  return os << t.toString(0);
}
