#pragma once

#include <deque>
#include <utility>

#include "s21_graph_algorithms/Deque.hpp"

namespace s21::graph_algorithms {

template <typename T>
class Queue : public Deque<T> {
 public:
  static auto queue() { return Queue(); }

  using std::deque<T>::front;
  using std::deque<T>::back;

  template <typename... Args>
  auto pop(Args&&... args) {
    return this->Deque<T>::pop_back(std::forward<decltype(args)>(args)...);
  }
};

}  // namespace s21::graph_algorithms
