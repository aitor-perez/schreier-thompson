// Graph.h
#ifndef Graph_H
#define Graph_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class Vertex {
  vector<Vertex*> neighbors;

public:
  Vertex() {
    neighbors = vector<Vertex*>(0);
  }

  ~Vertex() {
    for (int i=0; i<neighbors.size(); i++) {
      delete neighbors[i];
    }
  }

  vector<Vertex*> adjacent();
  void addNeighbor(Vertex* v);

  //string name() const;
  //friend ostream &operator<<(ostream &os, Vertex const &v);
};

class Graph {
  vector<Vertex*> vertices;

public:
  Graph() {
    vertices = vector<Vertex*>(0);
  }

  Graph(int n) {
    vertices = vector<Vertex*>(n);
    for (int i=0; i<vertices.size(); i++) {
      vertices[i] = new Vertex();
    }
  }

  ~Graph() {
    for (int i=0; i<vertices.size(); i++) {
      delete vertices[i];
    }
  }

  Vertex* getVertex(int i) const;
  void addEdge(int i, int j);
  bool isBipartite();

  friend ostream &operator<<(ostream &os, Graph const &gamma);
};

#endif