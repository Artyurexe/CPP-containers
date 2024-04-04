#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class stack {
 private:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  list<T> list;

 public:
  stack() : list(){};
  stack(std::initializer_list<value_type> const &items) {
    for (auto it : items) list.push_front(it);
  }
  stack(const stack &other) : list(other.list){};
  stack(stack &&other) : list(other.list) { other.list.clear(); };
  stack operator=(stack &&other) {
    list.clear();
    list = other.list;
    other.list.clear();

    return *this;
  }

  ~stack() { list.clear(); }

  const_reference top() { return list.front(); }

  bool empty() { return list.empty(); }
  size_type size() { return list.size(); }

  void push(const_reference val) { list.push_front(val); }
  void pop() { list.pop_front(); }
  void swap(stack &other) { list.swap(other.list); }

  template <typename... Ts>
  void insert_many_front(Ts &&...vals) {
    (list.push_front(value_type(std::forward<Ts>(vals))), ...);
  }
};

}  // namespace s21
#endif  // SRC_STACK_H_