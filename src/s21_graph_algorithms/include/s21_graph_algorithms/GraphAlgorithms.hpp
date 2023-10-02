#pragma once

#include <vector>

#include "s21_graph.hpp"

namespace s21::graph_algorithms {

class GraphAlgorithms {
 private:
  struct t_deikstra {
    bool visited = false;
    unsigned long int mark = 4294967295;
    unsigned int number;
  };

  struct t_prim {
    long long int value;
    unsigned int vertex_from = 0;
    unsigned int vertex_to = 0;
  };

 public:
  struct t_ant {
    std::vector<int> way;
    double distance = 0;
    unsigned int way_back = 0;
    bool ant_can_go = true;
    double feromon = 0;
  };

  struct TsmResult {
    std::vector<int>
        vertices;  // массив с искомым маршрутом (с порядком обхода вершин).
                   // Вместо int* можно использовать std::vector<int>
    double distance;  // длина этого маршрута
  };

  // Part 1
  static std::vector<unsigned int> depthFirstSearch(graph::Graph& graph,
                                                    int startVertex);

  static std::vector<unsigned int> breadthFirstSearch(graph::Graph& graph,
                                                      int startVertex);

  // Part 2
  static int getShortestPathBetweenVertices(graph::Graph& graph, int vertex1,
                                            int vertex2);

  static graph::SquareMatrix<int> getShortestPathsBetweenAllVertices(
      graph::Graph& graph);

  // Part 3
  static graph::SquareMatrix<int> getLeastSpanningTree(graph::Graph& graph);

  // Part 4
  static TsmResult solveTravelingSalesmanProblem(graph::Graph& graph);

  // Bonus
  static TsmResult exhaustiveSearch(graph::Graph& graph);

  static TsmResult nearestNeighborAlgorithm(graph::Graph& graph);
};

}  // namespace s21::graph_algorithms
