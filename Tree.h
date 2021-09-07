// Tree.h
#ifndef Tree_H
#define Tree_H

#include <iostream>
#include <string>

using namespace std;

class Tree {
  Tree* l;
  Tree* r;
  Tree* p;

public:
  Tree() {
    l = NULL;
    r = NULL;
    p = NULL;
  }

  // Copy constructor
  Tree(Tree* t) {
    l = NULL;
    r = NULL;
    p = NULL;

    if (!t->isLeaf()) {
      l = new Tree(t->l);
      r = new Tree(t->r);

      l->p = this;
      r->p = this;
    }
  }

  ~Tree() {
    delete l;
    delete r;
  }

  Tree* left();
  Tree* right();
  Tree* parent();

  bool isLeaf() const;
  bool isCaret(int n);

  int leaves();

  Tree* getLeaf(int n);
  int findLeaf(Tree* leaf);
  void addCaret(int n);
  void removeCaret(int n);

  string toString(int offset) const;
  friend ostream &operator<<(ostream &os, Tree const &t);
};

#endif