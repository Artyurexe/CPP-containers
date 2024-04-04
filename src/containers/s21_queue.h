#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class queue {
 private:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  list<T> list;

 public:
  queue() : list(){};
  queue(std::initializer_list<value_type> const &items) {
    for (auto it : items) list.push_back(it);
  }
  queue(const queue &other) : list(other.list){};
  queue(queue &&other) : list(other.list) { other.list.clear(); };
  queue operator=(queue &&other) {
    list.clear();
    list = other.list;
    other.list.clear();

    return *this;
  }

  ~queue() { list.clear(); }

  const_reference front() { return list.front(); }
  const_reference back() { return list.back(); }

  bool empty() { return list.empty(); }
  size_type size() { return list.size(); }

  void push(const_reference val) { list.push_back(val); }
  void pop() { list.pop_front(); }
  void swap(queue &other) { list.swap(other.list); }

  template <typename... Ts>
  void insert_many_back(Ts &&...vals) {
    (list.push_back(value_type(std::forward<Ts>(vals))), ...);
  }
};

}  // namespace s21
#endif  // SRC_QUEUE_H_