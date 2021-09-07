// Pair.cpp
#include "Pair.h"

Tree* Pair::top() const {
  return t;
}

Tree* Pair::bottom() const {
  return b;
}

void Pair::addOpposingCarets(int n) {
  t->addCaret(n);
  b->addCaret(n);
}

void Pair::simplify() {
  int n = t->leaves();

  bool simplified = true;

  for (int i=1; i <= n; i++) {
    if (t->isCaret(i) and b->isCaret(i)) {
      simplified = false;
      t->removeCaret(i);
      b->removeCaret(i);
      break;
    }
  }

  if (!simplified) {
    this->simplify();
  }
}

void normalize(Pair* x, Pair* y, Tree* tx, Tree* ty) {
  if (tx->isLeaf() and ty->isLeaf()) {
    return;
  }

  if (tx->isLeaf() and !ty->isLeaf()) {
    int n = x->bottom()->findLeaf(tx);
    x->addOpposingCarets(n);
    normalize(x, y, tx, ty);
  }

  if (!tx->isLeaf() and ty->isLeaf()) {
    int n = y->top()->findLeaf(ty);
    y->addOpposingCarets(n);
    normalize(x, y, tx, ty);
  }

  if (!tx->isLeaf() and !ty->isLeaf()) {
    normalize(x, y, tx->left(), ty->left());
    normalize(x, y, tx->right(), ty->right());
  }
}

Pair* Pair::compose(Pair* p) {
  normalize(this, p, this->bottom(), p->top());

  Pair* q = new Pair(new Tree(this->top()), new Tree(p->bottom()));

  this->simplify();
  p->simplify();
  q->simplify();

  return q;
}


Graph* Pair::jones() {
  int n = t->leaves();

  Graph* gamma = new Graph(n);

  for (int i=0; i<n; i++) {
    for (int k=0; k<2; k++) {
      Tree* tree;

      if (k == 0) {
        tree = t;
      } else {
        tree = b;
      }

      Tree* child = tree->getLeaf(i+1);
      Tree* parent = child->parent();

      while (parent != NULL) {
        if (parent->right() == child) {
          int j = tree->findLeaf(parent->getLeaf(1));
          gamma->addEdge(j-1, i);
          break;
        } else {
          child = parent;
          parent = parent->parent();
        }
      }

    }
  }

  return gamma;
}

ostream &operator<<(ostream &os, Pair const &p) {
  return os << *p.top() << endl << *p.bottom();
}