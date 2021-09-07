#include "Graph.h"
#include "Tree.h"
#include "Pair.h"

void print(Tree* t, string pref) {
  cerr << pref << t << endl;
  cerr << pref << "L: " << t->left() << endl;
  cerr << pref << "R: " << t->right() << endl;
  cerr << pref << "P: " << t->parent() << endl;

  if (!t->isLeaf()) {
    print(t->left(), pref + "    ");
    print(t->right(), pref + "    ");
  }
}

// Returns a 3-dim matrix M such that every in M[L] row contains a word in 0..n-1 of length L+1, L in 0..l-1
vector<vector<vector<int> > > combinations(int n, int l) {
  if (l == 1) {
    vector<vector<int> > one_combs(n, vector<int>(1));
    
    for (int i=0; i<n; i++) {
      one_combs[i][0] = i;
    }

    vector<vector<vector<int> > > combs;
    combs.push_back(one_combs);
    return combs;
  }

  vector<vector<vector <int> > > combs = combinations(n, l-1);
  vector<vector<int> > prefixes = combs[l-2];

  vector<vector<int> > l_combs(0, vector<int>(l));

  for (int i=0; i < prefixes.size(); i++) {
    for (int j=0; j < n; j++) {
      // Avoiding inverses (01, 10, 23, 32, etc.)
      if (prefixes[i][l-2] % 2 == 0 and j == prefixes[i][l-2] + 1) {
        continue;
      }

      if (prefixes[i][l-2] % 2 == 1 and j == prefixes[i][l-2] - 1) {
        continue;
      }

      vector<int> l_comb = prefixes[i];
      l_comb.push_back(j);
      l_combs.push_back(l_comb);
    }
  }

  combs.push_back(l_combs);

  return combs;
}

string name(int i) {
  if (i==0) {
    return "\033[1;34mx0 \033[0m";
  } else if (i==1) {
    return "\033[1;31mx0i\033[0m";
  } else if (i==2) {
    return "\033[1;32mx1 \033[0m";
  } else if (i==3) {
    return "\033[1;35mx1i\033[0m";
  }

  return "boom";
}

int main() {
  Pair* x0 = new Pair(0);
  Pair* x1 = new Pair(1);

  Pair* x0i = new Pair(new Tree(x0->bottom()), new Tree(x0->top()));
  Pair* x1i = new Pair(new Tree(x1->bottom()), new Tree(x1->top()));

  vector<Pair*> generators;
  generators.push_back(x0);
  generators.push_back(x0i);
  generators.push_back(x1);
  generators.push_back(x1i);
  int n = generators.size();

  int length = 8;
  vector<vector<vector <int> > > combs = combinations(n, length);
  vector<vector<vector <int> > > rels(length);
  for (int l = 0; l < length; l++) {
    for (int i=0; i<combs[l].size(); i++) {
      Pair* x = new Pair();
      string s = "";

      for (int j=0; j<combs[l][i].size(); j++) {
        s += name(combs[l][i][j]) + " ";
        x = x->compose(generators[combs[l][i][j]]);
      }

      // Check that the word is not redundant
      bool redundant = false;
      for (int m=0; m < l and not redundant; m++) {
        for (int k=0; k < rels[m].size() and not redundant; k++) {
          vector<int> suffix(combs[l][i].end() - m - 1, combs[l][i].end());

          if (rels[m][k] == suffix) {
            redundant = true;
          }
        }
      }

      if (x->jones()->isBipartite() and not redundant) {
        rels[l].push_back(combs[l][i]);
        //cout << *x << endl;
        cout << s << " belongs to F->!" << endl;
      }

      delete x;
    }
  }
}
