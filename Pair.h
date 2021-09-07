// Pair.h
#ifndef Pair_H
#define Pair_H
#include "Graph.h"
#include "Tree.h"

#include <iostream>
#include <string>

using namespace std;

class Pair {
private:
  Tree* t;
  Tree* b;

public:
  Pair() {
    t = new Tree();
    b = new Tree();
  }

  Pair(int n) {
    t = new Tree();
    b = new Tree();

    if (n == 0) {
      // Element x0
      t->addCaret(1);
      t->addCaret(1);

      b->addCaret(1);
      b->addCaret(2);
    }
    
    if (n == 1) {
      // Element x1
      t->addCaret(1);
      t->addCaret(2);
      t->addCaret(2);

      b->addCaret(1);
      b->addCaret(2);
      b->addCaret(3);
    }
  }

  Pair(Tree* t, Tree* b) {
    this->t = new Tree(t);
    this->b = new Tree(b);
  }

  ~Pair() {
    delete t;
    delete b;
  }

  Tree* top() const;
  Tree* bottom() const;

  void addOpposingCarets(int n);

  void simplify();
  Pair* compose(Pair* p);

  Graph* jones();

  friend ostream &operator<<(ostream &os, Pair const &p);
};

#endif