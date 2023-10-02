#include <chrono>
#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "s21_graph.hpp"
#include "s21_graph_algorithms.hpp"
#include "s21_graph_algorithms/GraphAlgorithms.hpp"

using s21::graph::Graph;
using s21::graph::SquareMatrix;

using s21::graph_algorithms::GraphAlgorithms;

using s21::graph_algorithms::Deque;
using s21::graph_algorithms::Queue;
using s21::graph_algorithms::Stack;

class ReplException : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

void bruh() { std::cout << "currently there is no loaded graph" << std::endl; }

void handleHelp() {
  std::cout
      << "S21 Graph CLI reference:\n"
         "This is a REPL that operates on the currently loaded graph with user "
         "commands.\n\n"
         "Available commands:\n"
         "\tload - loads graph from an adjacency matrix file\n"
         "\tgraph - displays the loaded graph as an adjacency matrix\n"
         "\texport - exports the graph to a dot file\n"
         "\tdepth - traverses the graph in depth\n"
         "\tbreadth - traverses the graph in breadth\n"
         "\tpath - finds the shortest path between 2 vertices\n"
         "\tpaths - searches for shortest paths between all pairs of vertices\n"
         "\tmst - searches for the minimal spanning tree in the graph\n"
         "\ttsp - solves the traveling salesman problem for the graph\n"
         "\ttsp_compare - benchmarks 3 different TSP algorithms\n"
         "\thelp - displays this message\n"
         "\texit - exits the REPL\n"
      << std::endl;
}

void handleLoad(std::unique_ptr<Graph>& current_graph) {
  std::cout << "Enter graph file path: ";

  std::string path;
  std::cin >> path;

  auto graph = std::make_unique<Graph>();

  try {
    graph->loadGraphFromFile(path);
  } catch (std::exception& e) {
    std::ostringstream ss;

    ss << "Unable to read graph file: " << e.what();

    throw ReplException(ss.str());
  }

  current_graph = std::move(graph);

  std::cout << "graph loaded successfully" << std::endl;
}

void handleGraph(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  std::cout << *current_graph << std::endl;
}

void handleExport(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  std::cout << "Enter dot file path: ";

  std::string path;
  std::cin >> path;

  try {
    current_graph->exportGraphToDot(path);
  } catch (std::exception& e) {
    std::ostringstream ss;

    ss << "Unable to write graph file: " << e.what();

    throw ReplException(ss.str());
  }

  std::cout << "graph exported successfully" << std::endl;
}

void handleDepth(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  std::cout << "Enter starting vertex: ";

  int vertex;
  std::cin >> vertex;

  auto traversal = GraphAlgorithms::depthFirstSearch(*current_graph, vertex);

  std::cout << "Depth traversal: ";

  for (auto vertex : traversal) std::cout << vertex << " ";

  std::cout << std::endl;
}

void handleBreadth(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  std::cout << "Enter starting vertex: ";

  int vertex;
  std::cin >> vertex;

  auto traversal = GraphAlgorithms::breadthFirstSearch(*current_graph, vertex);

  std::cout << "Breadth traversal: ";

  for (auto vertex : traversal) std::cout << vertex << " ";

  std::cout << std::endl;
}

void handlePath(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  std::cout << "Enter starting vertex: ";

  int start;
  std::cin >> start;

  std::cout << "Enter ending vertex: ";

  int end;
  std::cin >> end;

  auto path = GraphAlgorithms::getShortestPathBetweenVertices(*current_graph,
                                                              start, end);

  std::cout << "Shortest path: " << path << std::endl;
}

void handlePaths(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  auto paths =
      GraphAlgorithms::getShortestPathsBetweenAllVertices(*current_graph);

  std::cout << "Shortest paths: " << paths << std::endl;
}

void handleMST(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  auto mst = GraphAlgorithms::getLeastSpanningTree(*current_graph);

  std::cout << "Minimal spanning tree: " << mst << std::endl;
}

void handleTSP(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  auto result = GraphAlgorithms::solveTravelingSalesmanProblem(*current_graph);

  std::cout << "Shortest path: ";

  for (auto vertex : result.vertices) std::cout << vertex << " ";

  std::cout << std::endl;

  std::cout << "Distance: " << result.distance << std::endl;
}

void handleTSPCompare(std::unique_ptr<Graph>& current_graph) {
  if (!current_graph) return bruh();

  std::cout << "Enter iteration count: ";

  int iterations;
  std::cin >> iterations;

  std::cout << "Running ant colony algorithm..." << std::endl;

  {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto i = 0; i < iterations; i++)
      GraphAlgorithms::solveTravelingSalesmanProblem(*current_graph);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Ant colony algorithm: " << duration.count() << "us"
              << std::endl;
  }

  std::cout << "Running exhaustive search..." << std::endl;

  {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto i = 0; i < iterations; i++)
      GraphAlgorithms::exhaustiveSearch(*current_graph);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Exhaustive search: " << duration.count() << "us" << std::endl;
  }

  std::cout << "Running nearest neighbour algorithm..." << std::endl;

  {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto i = 0; i < iterations; i++)
      GraphAlgorithms::nearestNeighborAlgorithm(*current_graph);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Nearest neighbour: " << duration.count() << "us" << std::endl;
  }
}

void handle_command(const std::string& command,
                    std::unique_ptr<Graph>& current_graph) {
  if (command == "load") {
    handleLoad(current_graph);
  } else if (command == "graph") {
    handleGraph(current_graph);
  } else if (command == "export") {
    handleExport(current_graph);
  } else if (command == "depth") {
    handleDepth(current_graph);
  } else if (command == "breadth") {
    handleBreadth(current_graph);
  } else if (command == "path") {
    handlePath(current_graph);
  } else if (command == "paths") {
    handlePaths(current_graph);
  } else if (command == "mst") {
    handleMST(current_graph);
  } else if (command == "tsp") {
    handleTSP(current_graph);
  } else if (command == "tsp_compare") {
    handleTSPCompare(current_graph);
  }
}

void start_repl() {
  std::unique_ptr<Graph> current_graph = nullptr;

  while (true) {
    std::cout << "$: ";

    std::string command;
    std::cin >> command;

    if (command == "help") {
      handleHelp();
    } else if (command == "exit") {
      break;
    }

    try {
      handle_command(command, current_graph);
    } catch (ReplException& e) {
      std::cout << "Repl error: " << e.what() << std::endl;
    }
  }
}

int main() {
  std::cout << "Welcome to the graph REPL!" << std::endl;
  std::cout << "Enter 'help' for a list of commands." << std::endl;

  try {
    start_repl();
  } catch (std::exception& e) {
    std::cout << "Fatal error: " << e.what() << std::endl;
  }
}
