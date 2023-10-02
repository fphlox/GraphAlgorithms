#include "s21_graph/Graph.hpp"

#include <fstream>
#include <limits>
#include <stdexcept>
#include <vector>

using Graph = s21::graph::Graph;

Graph::Graph(const std::string& name) : name(name), adjacencyMatrix_(0) {}

Graph::Graph(std::initializer_list<std::initializer_list<int>> adjacencyMatrix)
    : adjacencyMatrix_(adjacencyMatrix) {}

int& Graph::edge(std::size_t vertex1, std::size_t vertex2) {
  return adjacencyMatrix_(vertex1, vertex2);
}

const int& Graph::edge(std::size_t vertex1, std::size_t vertex2) const {
  return adjacencyMatrix_(vertex1, vertex2);
}

std::size_t Graph::vertexCount() const { return adjacencyMatrix_.size(); }

void Graph::importAsAdjacencyMatrix(std::istream& reader) {
  std::size_t vertexCount;

  reader >> vertexCount;

  SquareMatrix<int> adjacencyMatrix(vertexCount);

  for (std::size_t i = 0; i < vertexCount; i++) {
    for (std::size_t j = 0; j < vertexCount; j++) {
      reader >> adjacencyMatrix(i, j);
    }
  }

  adjacencyMatrix_ = std::move(adjacencyMatrix);
}

void Graph::exportAsDot(std::ostream& writer) const {
  writer << "digraph " << name << " {\n";

  for (std::size_t i = 0; i < vertexCount(); i++) {
    for (std::size_t j = 0; j < vertexCount(); j++) {
      auto currentEdge = edge(i, j);

      if (currentEdge == 0) {
        continue;
      }

      auto mirrorEdge = edge(j, i);

      if (currentEdge == mirrorEdge && i >= j) {
        writer << "\t" << i + 1 << " -> " << j + 1 << " [weight=" << currentEdge
               << ",dir=none]\n";
      }

      if (currentEdge != mirrorEdge) {
        writer << "\t" << i + 1 << " -> " << j + 1 << " [weight=" << currentEdge
               << "]\n";
      }
    }
  }

  writer << "}" << std::endl;
}

bool Graph::checkConnectivity() const {
  s21::graph::SquareMatrix<long> matrix(vertexCount());

  for (std::size_t j = 0; j < vertexCount(); j++) {
    for (std::size_t i = 0; i < vertexCount(); i++) {
      matrix(j, i) = edge(j, i);
      if (matrix(j, i) == 0)
        matrix(j, i) = std::numeric_limits<unsigned>::max();
      if (i == j) matrix(j, i) = 0;
    }
  }

  for (std::size_t k = 0; k < vertexCount(); k++) {
    for (std::size_t j = 0; j < vertexCount(); j++) {
      for (std::size_t i = 0; i < vertexCount(); i++) {
        matrix(j, i) = std::min(matrix(j, i), matrix(j, k) + matrix(k, i));
      }
    }
  }

  for (std::size_t j = 0; j < vertexCount(); j++) {
    for (std::size_t i = 0; i < vertexCount(); i++) {
      if (matrix(j, i) == std::numeric_limits<unsigned>::max()) return false;
    }
  }
  return true;
}

void Graph::loadGraphFromFile(std::string filename) {
  std::ifstream reader(filename);

  if (reader.fail()) {
    throw std::runtime_error("Could not open graph file");
  }

  importAsAdjacencyMatrix(reader);
  if (checkConnectivity() == false)
    throw std::runtime_error("Ошибка! Матрица не связна!");
}

void Graph::exportGraphToDot(std::string filename) const {
  std::ofstream writer(filename);

  if (writer.fail()) {
    throw std::runtime_error("Could not open graph file");
  }

  exportAsDot(writer);
}

std::ostream& s21::graph::operator<<(std::ostream& os, const Graph& graph) {
  os << graph.adjacencyMatrix_;

  return os;
}
