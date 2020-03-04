#include "dijkstra.h"

#include <climits>

int minDistance(const std::vector<int>& dist, std::vector<bool>& sptSet) {
  // Initialize min value
  int min = INT_MAX, min_index;

  for (int v = 0; v < dist.size(); v++)
    if (sptSet[v] == false && dist[v] <= min) min = dist[v], min_index = v;

  return min_index;
}

int dijkstra(const std::vector<std::vector<int>>& graph, int src,
             int destination) {
  std::vector<int> dist(
      graph.size());  // The output array.  dist[i] will hold the shortest
  // distance from src to i

  std::vector<bool> sptSet(graph.size());  // sptSet[i] will be true if vertex i
                                           // is included in shortest
  // path tree or shortest distance from src to i is finalized

  // Initialize all distances as INFINITE and stpSet[] as false
  for (int i = 0; i < graph.size(); i++) dist[i] = INT_MAX, sptSet[i] = false;

  // Distance of source vertex from itself is always 0
  dist[src] = 0;

  // Find shortest path for all vertices
  for (int count = 0; count < graph.size() - 1; count++) {
    // Pick the minimum distance vertex from the set of vertices not
    // yet processed. u is always equal to src in the first iteration.
    int u = minDistance(dist, sptSet);

    // Mark the picked vertex as processed
    sptSet[u] = true;

    // Update dist value of the adjacent vertices of the picked vertex.
    for (int v = 0; v < graph.size(); v++)

      // Update dist[v] only if is not in sptSet, there is an edge from
      // u to v, and total weight of path from src to  v through u is
      // smaller than current value of dist[v]
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
          dist[u] + graph[u][v] < dist[v])
        dist[v] = dist[u] + graph[u][v];
  }

  return dist[destination];
}