#include <gtest/gtest.h>

#include <cstdio>
#include <iostream>

#include "s21_graph.hpp"
#include "s21_graph_algorithms.hpp"

// Эта хрень здесь чтобы показать что текут гугл тесты а не проект
// #include <stdexcept>
// TEST(test, tester) {throw std::runtime_error("LOL");}

// GRAPH

TEST(Graph, init) { EXPECT_NO_THROW(s21::graph::Graph gr); }

TEST(Graph, load) {
  s21::graph::Graph gr;
  EXPECT_NO_THROW(gr.loadGraphFromFile("src/test/data/chekConnection/file1"));
}

TEST(Graph, edge) {
  s21::graph::Graph gr;
  gr.loadGraphFromFile("src/test/data/chekConnection/file1");
  EXPECT_EQ(gr.edge(2, 0), 11);
}

TEST(Graph, vertexCount) {
  s21::graph::Graph gr;
  gr.loadGraphFromFile("src/test/data/chekConnection/file1");
  EXPECT_EQ(gr.vertexCount(), 4);
}

TEST(Graph, export) {
  s21::graph::Graph gr;
  gr.loadGraphFromFile("src/test/data/chekConnection/file1");
  EXPECT_NO_THROW(gr.exportGraphToDot("bin/coverage/test/__output__/DOT"));
}

// CHECK CONNECTION

TEST(Connection, full) {
  s21::graph::Graph gr;
  gr.loadGraphFromFile("src/test/data/chekConnection/file1");
  EXPECT_EQ(gr.checkConnectivity(), true);
}

TEST(Connection, minimum) {
  s21::graph::Graph gr;

  gr.loadGraphFromFile("src/test/data/chekConnection/file2");
  EXPECT_EQ(gr.checkConnectivity(), true);
}

TEST(Connection, big) {
  s21::graph::Graph gr;

  gr.loadGraphFromFile("src/test/data/chekConnection/file3");
  EXPECT_EQ(gr.checkConnectivity(), true);
}

TEST(Connection, mini_fail) {
  s21::graph::Graph gr;

  EXPECT_ANY_THROW(gr.loadGraphFromFile("src/test/data/chekConnection/file4"));
}

TEST(Connection, zero_fail) {
  s21::graph::Graph gr;

  EXPECT_ANY_THROW(gr.loadGraphFromFile("src/test/data/chekConnection/file5"));
}

TEST(Connection, fail) {
  s21::graph::Graph gr;

  EXPECT_ANY_THROW(gr.loadGraphFromFile("src/test/data/chekConnection/file6"));
}

TEST(Connection, fail_half) {
  s21::graph::Graph gr;

  EXPECT_ANY_THROW(gr.loadGraphFromFile("src/test/data/chekConnection/file7"));
}

TEST(Connection, roll_sucsess) {
  s21::graph::Graph gr;

  gr.loadGraphFromFile("src/test/data/chekConnection/file8");
  EXPECT_EQ(gr.checkConnectivity(), true);
}

// ALGORITMS
// PART ONE

TEST(depthFirstSearch, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 4, 3, 2};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  std::vector<unsigned int> test = alg.depthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(depthFirstSearch, full_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{3, 4, 2, 1};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  std::vector<unsigned int> test = alg.depthFirstSearch(gr, 3);
  EXPECT_EQ(expected, test);
}

TEST(depthFirstSearch, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 2};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file2");
  std::vector<unsigned int> test = alg.depthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(depthFirstSearch, normal) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 2, 6, 5, 4, 3};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  std::vector<unsigned int> test = alg.depthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(depthFirstSearch, normal_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{5, 6, 2, 4, 3, 1};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  std::vector<unsigned int> test = alg.depthFirstSearch(gr, 5);
  EXPECT_EQ(expected, test);
}

TEST(depthFirstSearch, roll) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 2, 3, 4, 5, 6};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  std::vector<unsigned int> test = alg.depthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(depthFirstSearch, roll_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{6, 1, 2, 3, 4, 5};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  std::vector<unsigned int> test = alg.depthFirstSearch(gr, 6);
  EXPECT_EQ(expected, test);
}

// breadthFirstSearch

TEST(breadthFirstSearch, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 2, 3, 4};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  std::vector<unsigned int> test = alg.breadthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(breadthFirstSearch, full_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{3, 1, 2, 4};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  std::vector<unsigned int> test = alg.breadthFirstSearch(gr, 3);
  EXPECT_EQ(expected, test);
}

TEST(breadthFirstSearch, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 2};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file2");
  std::vector<unsigned int> test = alg.breadthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(breadthFirstSearch, normal) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 2, 3, 4, 6, 5};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  std::vector<unsigned int> test = alg.breadthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(breadthFirstSearch, normal_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{5, 6, 2, 1, 3, 4};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  std::vector<unsigned int> test = alg.breadthFirstSearch(gr, 5);
  EXPECT_EQ(expected, test);
}

TEST(breadthFirstSearch, roll) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{1, 2, 3, 4, 5, 6};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  std::vector<unsigned int> test = alg.breadthFirstSearch(gr, 1);
  EXPECT_EQ(expected, test);
}

TEST(breadthFirstSearch, roll_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  std::vector<unsigned int> expected{6, 1, 2, 3, 4, 5};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  std::vector<unsigned int> test = alg.breadthFirstSearch(gr, 6);
  EXPECT_EQ(expected, test);
}

// PART TWO
// getShortestPathBetweenVertices

TEST(getShortestPathBetweenVertices, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  test = alg.getShortestPathBetweenVertices(gr, 1, 4);
  EXPECT_EQ(56, test);
}

TEST(getShortestPathBetweenVertices, full_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  test = alg.getShortestPathBetweenVertices(gr, 3, 2);
  EXPECT_EQ(21, test);
}

TEST(getShortestPathBetweenVertices, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file2");
  test = alg.getShortestPathBetweenVertices(gr, 1, 2);
  EXPECT_EQ(1, test);
}

TEST(getShortestPathBetweenVertices, mini_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file2");
  test = alg.getShortestPathBetweenVertices(gr, 2, 1);
  EXPECT_EQ(5, test);
}

TEST(getShortestPathBetweenVertices, normal) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  test = alg.getShortestPathBetweenVertices(gr, 1, 5);
  EXPECT_EQ(421, test);
}

TEST(getShortestPathBetweenVertices, normal_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  test = alg.getShortestPathBetweenVertices(gr, 4, 6);
  EXPECT_EQ(90, test);
}

TEST(getShortestPathBetweenVertices, roll) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  test = alg.getShortestPathBetweenVertices(gr, 1, 6);
  EXPECT_EQ(20, test);
}

TEST(getShortestPathBetweenVertices, roll_II) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  int test;

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  test = alg.getShortestPathBetweenVertices(gr, 5, 4);
  EXPECT_EQ(16, test);
}

//    getShortestPathsBetweenAllVertices

TEST(getShortestPathsBetweenAllVertices, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {
      {0, 26, 5, 56}, {32, 0, 21, 30}, {11, 21, 0, 51}, {62, 30, 51, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  matrix = alg.getShortestPathsBetweenAllVertices(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

TEST(getShortestPathsBetweenAllVertices, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {{0, 1}, {5, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file2");
  matrix = alg.getShortestPathsBetweenAllVertices(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

TEST(getShortestPathsBetweenAllVertices, normal) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {
      {0, 356, 377, 386, 421, 416}, {32, 0, 21, 30, 65, 60},
      {11, 21, 0, 51, 86, 81},      {62, 30, 51, 0, 95, 90},
      {97, 65, 86, 95, 0, 5},       {92, 60, 81, 90, 5, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  matrix = alg.getShortestPathsBetweenAllVertices(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

TEST(getShortestPathsBetweenAllVertices, roll) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {
      {0, 2, 5, 9, 14, 20},   {19, 0, 3, 7, 12, 18}, {16, 18, 0, 4, 9, 15},
      {12, 14, 17, 0, 5, 11}, {7, 9, 12, 16, 0, 6},  {1, 3, 6, 10, 15, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  matrix = alg.getShortestPathsBetweenAllVertices(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

// PART THREE
// getLeastSpanningTree

TEST(getLeastSpanningTree, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {
      {0, 0, 5, 0}, {0, 0, 21, 30}, {11, 21, 0, 0}, {0, 30, 0, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file1");
  matrix = alg.getLeastSpanningTree(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

TEST(getLeastSpanningTree, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {{0, 1}, {5, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file2");
  matrix = alg.getLeastSpanningTree(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

TEST(getLeastSpanningTree, normal) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {
      {0, 356, 0, 0, 0, 0}, {356, 0, 21, 30, 0, 60}, {0, 21, 0, 0, 0, 0},
      {0, 30, 0, 0, 0, 0},  {0, 0, 0, 0, 0, 5},      {0, 60, 0, 0, 5, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file3");
  matrix = alg.getLeastSpanningTree(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

TEST(getLeastSpanningTree, roll) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph::SquareMatrix<int> matrix(0);
  s21::graph::SquareMatrix<int> matrix_expect = {
      {0, 2, 0, 0, 0, 0}, {0, 0, 3, 0, 0, 0}, {0, 0, 0, 4, 0, 0},
      {0, 0, 0, 0, 5, 0}, {0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}};

  gr.loadGraphFromFile("src/test/data/GraphAlgorithms/file4");
  matrix = alg.getLeastSpanningTree(gr);
  EXPECT_EQ(matrix_expect, matrix);
}

// PART FOUR
// solveTravelingSalesmanProblem

TEST(solveTravelingSalesmanProblem, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file1");
  rezult = alg.solveTravelingSalesmanProblem(gr);
  EXPECT_EQ(rezult.distance, 118);
}

TEST(solveTravelingSalesmanProblem, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file2");
  rezult = alg.solveTravelingSalesmanProblem(gr);
  EXPECT_EQ(rezult.distance, 6);
}

TEST(solveTravelingSalesmanProblem, big) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file3");
  rezult = alg.solveTravelingSalesmanProblem(gr);
  EXPECT_EQ(rezult.distance, 123);
}

// BONUS
// exhaustiveSearch

TEST(exhaustiveSearch, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file1");
  rezult = alg.exhaustiveSearch(gr);
  EXPECT_EQ(rezult.distance, 118);
}

TEST(exhaustiveSearch, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file2");
  rezult = alg.exhaustiveSearch(gr);
  EXPECT_EQ(rezult.distance, 6);
}

TEST(exhaustiveSearch, big) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file3");
  rezult = alg.exhaustiveSearch(gr);
  EXPECT_EQ(rezult.distance, 123);
}

// nearestNeighborAlgorithm

TEST(nearestNeighborAlgorithm, full) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file1");
  rezult = alg.nearestNeighborAlgorithm(gr);
  EXPECT_EQ(rezult.distance, 118);
}

TEST(nearestNeighborAlgorithm, mini) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file2");
  rezult = alg.nearestNeighborAlgorithm(gr);
  EXPECT_EQ(rezult.distance, 6);
}

TEST(nearestNeighborAlgorithm, big) {
  s21::graph::Graph gr;
  s21::graph_algorithms::GraphAlgorithms alg;
  s21::graph_algorithms::GraphAlgorithms::TsmResult rezult;

  gr.loadGraphFromFile("src/test/data/TravelingSalesmanProblem/file3");
  rezult = alg.nearestNeighborAlgorithm(gr);
  EXPECT_EQ(rezult.distance, 123);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
