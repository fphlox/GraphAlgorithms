#include "s21_graph_algorithms/GraphAlgorithms.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

#include "s21_graph_algorithms/Queue.hpp"
#include "s21_graph_algorithms/Stack.hpp"

static bool findInList(std::vector<unsigned> &spisok, unsigned number) {
  unsigned i;
  unsigned size = spisok.size();

  for (i = 0; i < size; i++) {
    if (spisok[i] == number) return (true);
  }
  return (false);
}

static bool findInList(std::vector<int> &spisok, int number) {
  unsigned i;
  unsigned size = spisok.size();

  for (i = 0; i < size; i++) {
    if (spisok[i] == number) return (true);
  }
  return (false);
}

static void lookAround(s21::graph::Graph &graph, std::vector<unsigned> &spisok,
                       s21::graph_algorithms::Stack<unsigned> &stack,
                       unsigned matrixSize, unsigned top_number) {
  unsigned i;

  for (i = 0; i < matrixSize; i++) {
    if ((graph.edge(top_number - 1, i) != 0) && (top_number - 1 != i)) {
      if (findInList(spisok, i + 1) == false) stack.push(i + 1);
    }
  }
}

static void lookAround(s21::graph::Graph &graph, std::vector<unsigned> &spisok,
                       s21::graph_algorithms::Queue<unsigned> &queue,
                       unsigned matrixSize, unsigned top_number) {
  unsigned i;

  for (i = 0; i < matrixSize; i++) {
    if ((graph.edge(top_number - 1, i) != 0) && (top_number - 1 != i)) {
      if (findInList(spisok, i + 1) == false) queue.push(i + 1);
    }
  }
}

// Part 1

std::vector<unsigned> s21::graph_algorithms::GraphAlgorithms::depthFirstSearch(
    s21::graph::Graph &graph, int startVertex) {
  unsigned next_elem;
  int matrixSize = graph.vertexCount();
  std::vector<unsigned> spisok;
  s21::graph_algorithms::Stack<unsigned> stack;

  if (((startVertex) <= 0) || ((startVertex) > matrixSize))
    throw std::runtime_error(
        "Ошибка! Стартовая вершина графа имеет отрицательный, нулевой или "
        "больший максимального номер!");

  spisok.push_back(startVertex);
  lookAround(graph, spisok, stack, matrixSize, startVertex);
  while (stack.size() > 0) {
    next_elem = stack.pop();
    if (findInList(spisok, next_elem) == false) spisok.push_back(next_elem);
    lookAround(graph, spisok, stack, matrixSize, next_elem);
  }
  return (spisok);
}

std::vector<unsigned>
s21::graph_algorithms::GraphAlgorithms::breadthFirstSearch(
    s21::graph::Graph &graph, int startVertex) {
  unsigned next_elem;
  int matrixSize = graph.vertexCount();
  std::vector<unsigned> spisok;
  s21::graph_algorithms::Queue<unsigned> queue;

  if (((startVertex) <= 0) || ((startVertex) > matrixSize))
    throw std::runtime_error(
        "Ошибка! Стартовая вершина графа имеет отрицательный, нулевой или "
        "больший максимального номер!");
  spisok.push_back(startVertex);
  lookAround(graph, spisok, queue, matrixSize, startVertex);
  while (queue.size() > 0) {
    // next_elem = queue.peek();
    next_elem = queue.pop();
    if (findInList(spisok, next_elem) == false) spisok.push_back(next_elem);
    // queue.pop();
    lookAround(graph, spisok, queue, matrixSize, next_elem);
  }
  return (spisok);
}

// Part 2
int s21::graph_algorithms::GraphAlgorithms::getShortestPathBetweenVertices(
    s21::graph::Graph &graph, int vertex1, int vertex2) {
  std::vector<t_deikstra> vertexes;
  s21::graph_algorithms::Queue<unsigned> need_to_visite;
  t_deikstra we_here;
  auto matrix_size = graph.vertexCount();

  if (((vertex1) <= 0) || (((std::size_t)vertex1) > matrix_size))
    throw std::runtime_error(
        "Ошибка! Стартовая вершина графа имеет отрицательный, нулевой или "
        "больший максимального номер!");
  if (((vertex2) <= 0) || (((std::size_t)vertex2) > matrix_size))
    throw std::runtime_error(
        "Ошибка! Искомая вершина графа имеет отрицательный, нулевой или "
        "больший максимального номер!");

  for (std::size_t i = 0; i < matrix_size; i++) {
    vertexes.push_back(we_here);
    vertexes[i].number = i + 1;
  }
  vertexes[vertex1 - 1].mark = 0;
  need_to_visite.push(vertex1);
  while (need_to_visite.size() != 0) {
    if (vertexes[need_to_visite.front() - 1].visited == false) {
      we_here = vertexes[need_to_visite.front() - 1];
      need_to_visite.pop();
      for (std::size_t i = 0; i < matrix_size; i++) {
        if ((graph.edge(we_here.number - 1, i) != 0) &&
            ((we_here.number - 1) != i)) {
          if (vertexes[i].visited == false) need_to_visite.push(i + 1);
          if ((we_here.mark + graph.edge(we_here.number - 1, i)) <
              vertexes[i].mark)
            vertexes[i].mark =
                (we_here.mark + graph.edge(we_here.number - 1, i));
        }
      }
      vertexes[we_here.number - 1].visited = true;
    } else
      need_to_visite.pop();
  }
  return (vertexes[vertex2 - 1].mark);
}

s21::graph::SquareMatrix<int>
s21::graph_algorithms::GraphAlgorithms::getShortestPathsBetweenAllVertices(
    s21::graph::Graph &graph) {
  auto matrix_size = graph.vertexCount();
  s21::graph::SquareMatrix<long> matrix(matrix_size);
  s21::graph::SquareMatrix<int> matrix_ret(matrix_size);

  for (std::size_t j = 0; j < matrix_size; j++) {
    for (std::size_t i = 0; i < matrix_size; i++) {
      matrix(j, i) = graph.edge(j, i);
      if (matrix(j, i) == 0) matrix(j, i) = std::numeric_limits<int>::max();
      if (i == j) matrix(j, i) = 0;
    }
  }

  for (std::size_t k = 0; k < matrix_size; k++) {
    for (std::size_t j = 0; j < matrix_size; j++) {
      for (std::size_t i = 0; i < matrix_size; i++) {
        if (matrix(j, i) > matrix(j, k) + matrix(k, i))
          matrix(j, i) = matrix(j, k) + matrix(k, i);
      }
    }
  }

  for (std::size_t j = 0; j < matrix_size; j++) {
    for (std::size_t i = 0; i < matrix_size; i++) {
      matrix_ret(j, i) = matrix(j, i);
    }
  }
  return matrix_ret;
}

// Part 3
// В данной реализации мы ищем в первую ояередь не самое маленькое дерево, а
// самое полноценное - тоесть то, по ветвям которого можно двигаться в обе
// стороны
s21::graph::SquareMatrix<int>
s21::graph_algorithms::GraphAlgorithms::getLeastSpanningTree(
    s21::graph::Graph &graph) {
  std::vector<unsigned> list;
  t_prim min = {};
  std::size_t currentSize;
  std::size_t matrixSize = graph.vertexCount();
  unsigned orientation;
  unsigned minorientation = matrixSize + 1;
  unsigned long result;
  unsigned long minResult = std::numeric_limits<long>::max();
  s21::graph::SquareMatrix<long> matrix(matrixSize);
  s21::graph::SquareMatrix<int> resultMatrix(matrixSize);
  s21::graph::SquareMatrix<int> minResultMatrix(matrixSize);

  for (std::size_t j = 0; j < matrixSize; j++) {
    for (std::size_t i = 0; i < matrixSize; i++) {
      matrix(j, i) = graph.edge(j, i);
      if (matrix(j, i) == 0)
        matrix(j, i) = std::numeric_limits<unsigned>::max();
      if (i == j) matrix(j, i) = 0;
    }
  }

  for (std::size_t k = 0; k < matrixSize; k++) {
    orientation = 0;
    result = 0;
    list.push_back(k + 1);
    while (list.size() < matrixSize) {
      // Алгоритм Прима
      currentSize = list.size();
      min.value = std::numeric_limits<unsigned>::max();
      for (std::size_t j = 0; j < currentSize; j++) {
        for (std::size_t i = 0; i < matrixSize; i++) {
          if ((matrix(list[j] - 1, i) < min.value) && (i != list[j] - 1) &&
              (findInList(list, i + 1) == false)) {
            min.value = matrix(list[j] - 1, i);
            min.vertex_from = list[j] - 1;
            min.vertex_to = i;
          }
        }
      }
      resultMatrix(min.vertex_from, min.vertex_to) =
          matrix(min.vertex_from, min.vertex_to);
      list.push_back(min.vertex_to + 1);
    }

    // Форматирование получившегося дерева, подсчет его ориентированности и
    // добавление двунаправленных частей матрицы
    for (std::size_t j = 0; j < matrixSize; j++) {
      for (std::size_t i = 0; i < matrixSize; i++) {
        if ((resultMatrix(j, i) != 0) &&
            ((matrix(i, j) == 0) ||
             (matrix(i, j) == std::numeric_limits<unsigned>::max())))
          orientation++;
        if ((resultMatrix(j, i) != 0) && (matrix(i, j) != 0) &&
            (matrix(i, j) != std::numeric_limits<unsigned>::max()))
          resultMatrix(i, j) = matrix(i, j);
      }
    }
    // Подсчет тяжести дерева
    for (std::size_t j = 0; j < matrixSize; j++) {
      for (std::size_t i = 0; i < matrixSize; i++) {
        result = result + resultMatrix(j, i);
      }
    }
    // Замена старого результата, при прохождении требований
    if (minorientation >= orientation) {
      if ((minResult > result) || (minorientation > orientation)) {
        minorientation = orientation;
        minResult = result;
        for (std::size_t j = 0; j < matrixSize; j++) {
          for (std::size_t i = 0; i < matrixSize; i++) {
            minResultMatrix(j, i) = resultMatrix(j, i);
          }
        }
      }
    }
    // Очистка перед новой итерацией алгоритма
    list.clear();
    for (std::size_t j = 0; j < matrixSize; j++) {
      for (std::size_t i = 0; i < matrixSize; i++) resultMatrix(j, i) = 0;
    }
  }
  return minResultMatrix;
}

// Part 4

unsigned wantVertex(s21::graph::Graph &graph,
                    const s21::graph::SquareMatrix<double> &fero_matrix,
                    s21::graph_algorithms::GraphAlgorithms::t_ant ant) {
  unsigned i;
  int j;
  double probability;
  double waysSum;
  std::vector<double> ways(graph.vertexCount(), 0);
  std::vector<double> want(graph.vertexCount(), 0);
  unsigned from = ant.way.back() - 1;

  waysSum = 0;
  // Подсчет привлекательности путей
  for (i = 0; i < graph.vertexCount(); i++) {
    if ((graph.edge(from, i) != 0) && (from != i) &&
        (findInList(ant.way, i + 1) == false))
      ways[i] = fero_matrix(from, i) / graph.edge(from, i);
    waysSum = waysSum + ways[i];
  }
  // Посчет вероятности выбора пути, в зависимости от привлекательности
  if (waysSum == 0) return (0);
  for (i = 0; i < graph.vertexCount(); i++) {
    want[i] = ways[i] / waysSum;
    if ((i != 0) && (want[i] != 0)) {
      j = i - 1;
      while (j >= 0) {
        if (want[j] != 0) {
          want[i] += want[j];
          break;
        }
        j--;
      }
    }
  }
  // Проброс вероятности и выбор пути
  probability = (double)(rand() % 1000 + 1) / 1000;
  for (i = 0; i < graph.vertexCount(); i++) {
    if ((want[i] != 0) && (probability <= want[i])) return (i + 1);
  }

  return (0);
}

s21::graph_algorithms::GraphAlgorithms::TsmResult
s21::graph_algorithms::GraphAlgorithms::solveTravelingSalesmanProblem(
    s21::graph::Graph &graph) {
  std::vector<t_ant> colony(graph.vertexCount());
  double feromon;
  s21::graph::SquareMatrix<double> fero_matrix(graph.vertexCount());
  unsigned vertex;
  unsigned long min_way_back;
  TsmResult rezult;
  bool need_retry;
  int retry;

  rezult.distance = std::numeric_limits<double>::infinity();
  feromon = 5;
  retry = 100;
  for (std::size_t j = 0; j != graph.vertexCount(); j++) {
    for (std::size_t i = 0; i != graph.vertexCount(); i++)
      fero_matrix(j, i) = 1;
  }
  while (retry > 0) {
    //Каждый муравей начинает со своей вершины графа
    for (std::size_t i = 0; i < colony.size(); i++)
      colony[i].way.push_back(i + 1);

    //Муравьи обходят граф
    for (std::size_t i = 0; i < graph.vertexCount(); i++) {
      while ((colony[i].way.size() < graph.vertexCount()) &&
             (colony[i].ant_can_go == true)) {
        if ((vertex = wantVertex(graph, fero_matrix, colony[i])) != 0) {
          colony[i].distance +=
              graph.edge(colony[i].way.back() - 1, vertex - 1);
          colony[i].way.push_back(vertex);
        } else
          colony[i].ant_can_go = false;
      }
      if (colony[i].ant_can_go == true)
        colony[i].way_back = getShortestPathBetweenVertices(
            graph, colony[i].way.back(), colony[i].way.front());
    }

    //Проверка на то, смог ли отработать алгоритм
    std::size_t j = 0;
    for (std::size_t i = 0; i < graph.vertexCount(); i++) {
      if (colony[i].ant_can_go == false) j++;
    }
    if (j == graph.vertexCount())
      throw std::runtime_error(
          "Ошибка! Все муравьи зашли в тупик! Муравьиный алгоритм не может "
          "обработать предоставленный граф!");

    //Находим минимальный путь возвращения для рассчета потерь ферамона
    min_way_back = std::numeric_limits<unsigned long>::infinity();
    for (std::size_t i = 0; i < graph.vertexCount(); i++) {
      if (colony[i].ant_can_go == true) {
        if (min_way_back > colony[i].way_back)
          min_way_back = colony[i].way_back;
      }
    }

    //рассчет потерь феромон от продолжительности возвращения
    for (std::size_t i = 0; i < graph.vertexCount(); i++) {
      if (colony[i].ant_can_go == true)
        colony[i].feromon =
            (feromon / 4) * 3 +
            ((feromon / 4) * (min_way_back / colony[i].way_back));
      else
        colony[i].feromon = 0;
    }

    //распыление феромон в зависимости от длины отрезков пути
    for (std::size_t j = 0; j < graph.vertexCount(); j++) {
      if (colony[j].ant_can_go == true) {
        for (std::size_t i = 0; i < graph.vertexCount() - 1; i++) {
          fero_matrix(colony[j].way[i] - 1, colony[j].way[i + 1] - 1) +=
              colony[j].feromon *
              ((colony[j].distance / graph.vertexCount()) /
               graph.edge(colony[j].way[i] - 1, colony[j].way[i + 1] - 1));
        }
      }
    }

    //получение минимального пути и проверка на необходимость повторений
    //алгоритма
    need_retry = false;
    for (std::size_t i = 0; i < graph.vertexCount(); i++) {
      if ((colony[i].distance + colony[i].way_back < rezult.distance) &&
          (colony[i].ant_can_go == true)) {
        rezult.distance = colony[i].distance + colony[i].way_back;
        rezult.vertices = colony[i].way;
        need_retry = true;
      }
    }
    if (need_retry == true) retry = 100;
    retry--;

    //обнуление муравьев перед следующей итерацией
    for (std::size_t i = 0; i < graph.vertexCount(); i++) {
      colony[i].ant_can_go = true;
      colony[i].feromon = 0;
      colony[i].way_back = 0;
      colony[i].distance = 0;
      colony[i].way.clear();
    }
  }

  return rezult;
}

// Bonus

void getWay(s21::graph::Graph &graph, std::vector<int> &way,
            s21::graph_algorithms::GraphAlgorithms::TsmResult &rezult) {
  double distance;
  std::size_t matrix_size = graph.vertexCount();

  std::size_t i = 0;
  while ((i < matrix_size) && (way.size() < matrix_size)) {
    if ((graph.edge(way.back() - 1, i) != 0) &&
        (findInList(way, i + 1) == false) && (way.size() < matrix_size)) {
      way.push_back(i + 1);
      getWay(graph, way, rezult);
    }
    i++;
  }

  if (way.size() == matrix_size) {
    distance = 0;
    for (i = 0; i < matrix_size - 1; i++) {
      distance += graph.edge(way[i] - 1, way[i + 1] - 1);
    }
    distance +=
        s21::graph_algorithms::GraphAlgorithms::getShortestPathBetweenVertices(
            graph, way.back(), way[0]);
    if (rezult.distance > distance) {
      rezult.vertices = way;
      rezult.distance = distance;
    }
  }
  way.pop_back();
}

s21::graph_algorithms::GraphAlgorithms::TsmResult
s21::graph_algorithms::GraphAlgorithms::exhaustiveSearch(
    s21::graph::Graph &graph) {
  std::vector<int> way;
  TsmResult rezult;

  rezult.distance = std::numeric_limits<double>::infinity();
  for (std::size_t i = 0; i < graph.vertexCount(); i++) {
    way.push_back(i + 1);
    getWay(graph, way, rezult);
  }
  return (rezult);
}

s21::graph_algorithms::GraphAlgorithms::TsmResult
s21::graph_algorithms::GraphAlgorithms::nearestNeighborAlgorithm(
    s21::graph::Graph &graph) {
  TsmResult rezult;
  unsigned min_verter;
  double min_way;
  double distance;
  std::vector<int> way;
  bool dead_end;
  std::size_t matrix_size = graph.vertexCount();

  rezult.distance = std::numeric_limits<double>::infinity();

  for (std::size_t j = 0; j < matrix_size; j++) {
    way.push_back(j + 1);
    dead_end = false;
    distance = 0;
    while ((way.size() < matrix_size) && (dead_end == false)) {
      min_verter = 0;
      min_way = std::numeric_limits<double>::infinity();
      for (std::size_t i = 0; i < matrix_size; i++) {
        if ((graph.edge(way.back() - 1, i) != 0) &&
            (way.back() - 1 != (int)i) && (findInList(way, i + 1) == false)) {
          if (graph.edge(way.back() - 1, i) < min_way) {
            min_way = graph.edge(way.back() - 1, i);
            min_verter = i + 1;
          }
        }
      }
      if (min_verter != 0) {
        way.push_back(min_verter);
        distance += min_way;
      } else
        dead_end = true;
    }
    if (dead_end == false) {
      distance += s21::graph_algorithms::GraphAlgorithms::
          getShortestPathBetweenVertices(graph, way.back(), way[0]);
      if (distance < rezult.distance) {
        rezult.distance = distance;
        rezult.vertices = way;
      }
    }
    way.clear();
  }
  return (rezult);
}
