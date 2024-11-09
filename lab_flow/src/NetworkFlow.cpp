#include <vector>
#include <algorithm>
#include <set>
#include <limits>

#include "cs225_graph/graph.h"
#include "cs225_graph/edge.h"

#include "NetworkFlow.h"


int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  residual_ = g_;
  flow_ = g_;

  vector<Edge> edges = g_.getEdges();
  for (Edge & e : edges){
    Vertex v1 = e.source;
    Vertex v2 = e.dest;
    // clear edge weights to zero
    flow_.setEdgeWeight(e.source, e.dest, 0);

    // set up inverse edges
    residual_.insertEdge(v2, v1);
    residual_.setEdgeWeight(v2, v1, 0);
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
  int maxCap = std::numeric_limits<int>::max();
  for(size_t i = 0; i < path.size() - 1; ++i){
    int currCap = residual_.getEdgeWeight(path[i], path[i + 1]);
    if(currCap < maxCap) maxCap = currCap;
  }
  return maxCap;
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
  while(findAugmentingPath(source_, sink_, path)){//there is a valid path
    int maxCap = pathCapacity(path);
    for(size_t i = 0; i < path.size() - 1; ++i){
      if(flow_.edgeExists(path[i], path[i + 1])){
        flow_.setEdgeWeight(path[i], path[i + 1], flow_.getEdgeWeight(path[i], path[i + 1]) + maxCap);
        //std::cout << __LINE__ << " path[i] = " << path[i]  << "; path[i + 1] " << path[i + 1]  << "; flowWeight + maxCap " << flow_.getEdgeWeight(path[i], path[i + 1]) + maxCap << std::endl;
      }else{
        flow_.setEdgeWeight(path[i + 1], path[i], flow_.getEdgeWeight(path[i + 1], path[i]) - maxCap);
        //std::cout << __LINE__ << " path[i + 1] = " << path[i + 1]  << "; path[i] " << path[i]  << "; upaded weight: " << flow_.getEdgeWeight(path[i + 1], path[i]) - maxCap << std::endl;
      }
      residual_.setEdgeWeight(path[i], path[i + 1], residual_.getEdgeWeight(path[i], path[i + 1]) - maxCap);
      //std::cout << __LINE__ << " path[i] = " << path[i]  << "; path[i + 1] " << path[i + 1]  <<"; upaded weight: " << residual_.getEdgeWeight(path[i], path[i + 1]) - maxCap << std::endl;

      residual_.setEdgeWeight(path[i + 1], path[i], residual_.getEdgeWeight(path[i + 1], path[i]) + maxCap);
      //std::cout << __LINE__ << " path[i + 1] = " << path[i + 1]  << "; path[i] " << path[i]  << "; upaded weight: "<< residual_.getEdgeWeight(path[i + 1], path[i]) + maxCap << std::endl;

    }
  }
  maxFlow_ = 0;
	for(Vertex v : flow_.getAdjacent(source_)){
		maxFlow_  += flow_.getEdgeWeight(source_, v);
	}
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
