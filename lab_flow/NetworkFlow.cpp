/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  for (Vertex v : g_.getVertices()) {
    residual_.insertVertex(v);
    flow_.insertVertex(v);
  }

  for (Edge e : g_.getEdges()) {
    residual_.insertEdge(e.source, e.dest);
    residual_.insertEdge(e.dest, e.source);

    residual_.setEdgeWeight(e.source, e.dest, e.getWeight());
    residual_.setEdgeWeight(e.dest, e.source, 0);

    flow_.insertEdge(e.source, e.dest);
    flow_.setEdgeWeight(e.source, e.dest, 0);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int min = INT16_MAX;
  vector<int> edges;
  for (unsigned i = 0; i < path.size() - 1; i++) {
    edges.push_back(residual_.getEdgeWeight(path[i], path[i + 1]));
    for (auto &e : edges) {
      if (e < min) {
        min = e;
      }
    }
  }
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  std::vector<Vertex> path;
  int max = 0;
  while (findAugmentingPath(source_, sink_, path)) {
    int currPathCapacity = pathCapacity(path);
    max += currPathCapacity;
    for (unsigned i = 0; i < path.size() - 1; i++) {
      Vertex currVertex = path[i];
      Vertex nextVertex = path[i + 1];

      if (flow_.edgeExists(currVertex, nextVertex)) {
        int currEdgeCap = flow_.getEdgeWeight(currVertex, nextVertex);
        flow_.setEdgeWeight(currVertex, nextVertex, currPathCapacity + currEdgeCap);
      } else {
        int currEdgeCap = flow_.getEdgeWeight(nextVertex, currVertex);
        flow_.setEdgeWeight(nextVertex, currVertex, currEdgeCap - currPathCapacity);
      }
      residual_.setEdgeWeight(currVertex, nextVertex, residual_.getEdgeWeight(currVertex, nextVertex) - currPathCapacity);
      residual_.setEdgeWeight(nextVertex, currVertex, residual_.getEdgeWeight(nextVertex, currVertex) + currPathCapacity);
    }
  }
  maxFlow_ = max;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

