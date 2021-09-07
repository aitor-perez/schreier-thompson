// Graph.cpp
#include "Graph.h"

vector<Vertex*> Vertex::adjacent() {
  return neighbors;
}

void Vertex::addNeighbor(Vertex* v) {
  for (int i=0; i < neighbors.size(); i++) {
    if (v == neighbors[i]) {
      return;
    }
  }

  neighbors.push_back(v);
}


Vertex* Graph::getVertex(int i) const {
  if (i < 0) {
    return NULL;
  }

  int n = vertices.size();
  if (i >= n) {
    return NULL;
  }

  return vertices[i];
}

void Graph::addEdge(int i, int j) {
  if (i < 0 or j < 0) {
    return;
  }

  int n = vertices.size();
  if (i >= n or j >= n) {
    return;
  }

  vertices[i]->addNeighbor(vertices[j]);
  vertices[j]->addNeighbor(vertices[i]);
}

bool Graph::isBipartite() {
  int n = vertices.size();

  if (n == 0) {
    return true;
  }

  map<Vertex*,int> color; // Default value 0
  queue<Vertex*> q; // Empty queue

  // Init
  color[vertices[0]] = 1;
  q.push(vertices[0]);

  // BFS
  while (!q.empty()) {
    Vertex* v = q.front();
    vector<Vertex*> neighbors = v->adjacent();

    for (int i=0; i<neighbors.size(); i++) {
      Vertex* w = neighbors[i];

      if (color[w] == 0) {
        color[w] = 1 + color[v] % 2; // Set color different to that of v
        q.push(w);
      } else if (color[v] == color[w]) {
        return false;
      }
    }

    q.pop();
  }

  return true;
}

ostream &operator<<(ostream &os, Graph const &gamma) {
  int n = gamma.vertices.size();

  for (int i=0; i<n; i++) {
    os << gamma.getVertex(i) << ":";

    vector<Vertex*> neighbors = gamma.getVertex(i)->adjacent();
    for (int j=0; j<neighbors.size(); j++) {
      os << " " << neighbors[j];
    }

    os << endl;
  }

  return os;
}
