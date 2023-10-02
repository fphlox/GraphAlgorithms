#pragma once

#include <deque>
#include <utility>

namespace s21::graph_algorithms {

// Базовый класс для стека и очереди
template <typename T>
class Deque : protected std::deque<T> {
 public:
  using std::deque<T>::deque;

  template <typename... Args>
  auto push(Args&&... args) {
    this->std::deque<T>::push_front(std::forward<decltype(args)>(args)...);

    return this->std::deque<T>::front();
  }

  template <typename... Args>
  auto pop_front(Args&&... args) {
    auto front = this->std::deque<T>::front();

    this->std::deque<T>::pop_front(std::forward<decltype(args)>(args)...);

    return front;
  }

  template <typename... Args>
  auto pop_back(Args&&... args) {
    auto front = this->std::deque<T>::back();

    this->std::deque<T>::pop_back(std::forward<decltype(args)>(args)...);

    return front;
  }

  using std::deque<T>::size;

  std::deque<T>& as_deque() { return *this; }
  const std::deque<T>& as_deque() const { return *this; }
};

}  // namespace s21::graph_algorithms
