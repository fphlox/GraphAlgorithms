#pragma once

#include <deque>
#include <utility>

#include "s21_graph_algorithms/Deque.hpp"

namespace s21::graph_algorithms {

template <typename T>
class Stack : public Deque<T> {
 public:
  static auto stack() { return Stack(); }

  auto top() { return this->std::deque<T>::front(); }

  template <typename... Args>
  auto pop(Args&&... args) {
    return this->Deque<T>::pop_front(std::forward<decltype(args)>(args)...);
  }
};

}  // namespace s21::graph_algorithms
