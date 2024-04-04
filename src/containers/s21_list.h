#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <set>

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class list {
 private:
  template <typename Type>
  class listNode;

  template <typename Node>
  class listIterator;

  template <typename Node>
  class listConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  listNode<T>* first = nullptr;
  listNode<T>* last = nullptr;
  size_t list_size = 0;

 public:
  using iterator = listIterator<listNode<T>>;
  using const_iterator = listConstIterator<listNode<T>>;

  /* List Functions */
  list() noexcept = default;
  list(size_type n);
  list(size_type n, T const& val);
  list(std::initializer_list<value_type> const& items);
  list(const list& other);
  list(list&& other);
  ~list() { clear(); }

  list& operator=(const list& other);
  list& operator=(list&& other);

  /* List Element access */
  const_reference front() const {
    return const_cast<const_reference>(first->value);
  }
  const_reference back() const {
    return const_cast<const_reference>(last->value);
  }

  /* List Iterators */
  iterator begin() const { return iterator(first); }
  iterator end() const { return iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(first); }
  const_iterator cend() const { return const_iterator(nullptr); }

  /* List Capacity */
  bool empty() { return !list_size; }
  size_type size() { return list_size; }
  size_type max_size();

  /* List Modifiers */
  void clear();
  iterator insert(iterator pos, const_reference val);
  void erase(iterator pos);

  void push_front(const_reference val) { insert(begin(), val); }
  void push_back(const_reference val) { insert(end(), val); }
  void pop_front() { erase(begin()); }
  void pop_back() { erase(last); }

  void swap(list& other);
  void reverse();
  void sort();
  void unique();
  void merge(list& other);
  void splice(const iterator c_pos, list& other);

  template <typename... Ts>
  iterator insert_many(const iterator c_pos, Ts&&... vals);

  template <typename... Ts>
  void insert_many_back(Ts&&... vals);

  template <typename... Ts>
  void insert_many_front(Ts&&... vals);
};

template <typename T>
template <typename Type>
class list<T>::listNode {
  friend class list<T>;
  friend class list<T>::listIterator<T>;
  friend class list<T>::listConstIterator<T>;

 private:
  Type value;
  listNode* next = nullptr;
  listNode* prev = nullptr;

  listNode() : value(Type()){};
  listNode(Type const& val) : value(val){};
};

template <typename T>
template <typename Node>
class list<T>::listIterator {
  friend class list;

 private:
  Node* iPtr;

  listIterator(Node* node) : iPtr(node){};

 public:
  using value_type = list::value_type;
  using pointer = value_type*;
  using reference = value_type&;
  using difference_type = std::ptrdiff_t;

  // listIterator(listConstIterator<T>& ci) : iPtr(ci.iPtr){};

  listIterator& operator++() {
    iPtr = iPtr->next ? iPtr->next : nullptr;
    return *this;
  }

  listIterator operator++(int) {
    listIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  listIterator& operator--() {
    iPtr = iPtr->prev ? iPtr->prev : nullptr;
    return *this;
  }

  listIterator operator--(int) {
    listIterator tmp = *this;
    --(*this);
    return tmp;
  }

  reference operator*() { return iPtr->value; }

  bool operator==(const listIterator& other) const {
    return iPtr == other.iPtr;
  }

  bool operator!=(const listIterator& other) const { return !(*this == other); }
};

template <typename T>
template <typename Node>
class list<T>::listConstIterator {
  friend class list;

 private:
  Node const* iPtr;

  listConstIterator(Node const* node) : iPtr(node){};

 public:
  using value_type = list::value_type const;
  using pointer = value_type*;
  using reference = value_type&;
  using difference_type = std::ptrdiff_t;

  listConstIterator& operator++() {
    iPtr = iPtr->next ? iPtr->next : nullptr;
    return *this;
  }

  listConstIterator operator++(int) {
    listConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  listConstIterator& operator--() {
    iPtr = iPtr->prev ? iPtr->prev : nullptr;
    return *this;
  }

  listConstIterator operator--(int) {
    listConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  reference operator*() { return iPtr->value; }

  bool operator==(const listConstIterator& other) const {
    return iPtr == other.iPtr;
  }

  bool operator!=(const listConstIterator& other) const {
    return !(*this == other);
  }
};

template <typename T>
list<T>::list(size_type n) : list{} {
  listNode<T>* new_node = new listNode<T>();
  first = last = new_node;
  ++list_size;

  for (size_type i = list_size; i != n; ++i) {
    listNode<T>* new_node = new listNode<T>();
    new_node->next = first;
    first->prev = new_node;
    first = new_node;
    ++list_size;
  }
}

template <typename T>
list<T>::list(size_type n, T const& val) : list{} {
  for (size_type i = list_size; i != n; ++i) push_back(val);
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list{} {
  for (auto it : items) push_back(it);
}

template <typename T>
list<T>::list(const list& other) : list{} {
  for (const auto& it : other) push_back(it);
}

template <typename T>
list<T>::list(list&& other)
    : first(other.first), last(other.last), list_size(other.list_size) {
  other.first = other.last = nullptr;
  other.list_size = 0;
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  clear();
  for (auto it : other) push_back(it);

  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) {
  clear();
  swap(other);

  return *this;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(listNode<T>);
}

template <typename T>
void list<T>::clear() {
  while (list_size > 1) pop_back();

  if (!empty()) {
    delete first;
    first = last = nullptr;
    list_size = 0;
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference val) {
  listNode<T>* new_node = new listNode<T>(val);

  if (!empty()) {
    new_node->next = pos.iPtr;
    new_node->prev = pos.iPtr ? pos.iPtr->prev : last;

    if (pos == end()) {
      last->next = new_node;
      last = new_node;
    } else if (pos != begin()) {
      pos.iPtr->prev->next = new_node;
      pos.iPtr->prev = new_node;
    } else if (pos == begin()) {
      pos.iPtr->prev = new_node;
      first = new_node;
    }
  } else {
    first = last = new_node;
  }

  ++list_size;
  return iterator(new_node);
}

template <typename T>
void list<T>::erase(iterator pos) {
  listNode<T>* tmp = pos.iPtr;

  if (pos.iPtr->next) pos.iPtr->next->prev = pos.iPtr->prev;
  if (pos.iPtr->prev) pos.iPtr->prev->next = pos.iPtr->next;

  if (pos.iPtr == first) first = pos.iPtr->next;
  if (pos.iPtr == last) last = pos.iPtr->prev;

  pos = pos.iPtr->next;
  delete tmp;

  --list_size;
}

template <typename T>
void list<T>::swap(list& other) {
  listNode<T>* tmp_first = other.first;
  listNode<T>* tmp_last = other.last;
  size_t tmp_size = other.list_size;

  other.first = first;
  other.last = last;
  other.list_size = list_size;

  first = tmp_first;
  last = tmp_last;
  list_size = tmp_size;
}

template <typename T>
void list<T>::reverse() {
  for (auto it = begin(); it != end(); --it) {
    listNode<T>* tmp = it.iPtr->prev;
    it.iPtr->prev = it.iPtr->next;
    it.iPtr->next = tmp;
  }

  listNode<T>* tmp = last;
  last = first;
  first = tmp;
}

template <typename T>
void list<T>::sort() {
  std::multiset<T> sortedList;

  for (auto const& it : *this) sortedList.insert(it);

  clear();

  for (auto const& it : sortedList) push_back(it);
}

template <typename T>
void list<T>::unique() {
  for (auto it = begin(); it != end(); ++it)
    if (it.iPtr->prev && it.iPtr->prev->value == it.iPtr->value)
      erase(it.iPtr->prev);
}

template <typename T>
void list<T>::merge(list& other) {
  sort();
  other.sort();

  if (empty()) {
    for (auto const& it : other) push_back(it);
  } else {
    auto it_oth = other.cbegin();
    for (auto it = begin(); it != end() && it_oth != other.cend(); ++it)
      while (it_oth != other.cend() && *it_oth <= *it) insert(it, *it_oth++);

    while (it_oth != other.cend()) insert(end(), *it_oth++);
  }
}

template <typename T>
void list<T>::splice(const iterator c_pos, list& other) {
  if (!other.empty()) {
    iterator pos = c_pos;

    for (iterator it = other.last;; --it) {
      insert(pos, *it);
      if (it == other.begin()) break;
      pos == end() ? pos = last : --pos;
    }

    other.clear();
  }
}

template <typename T>
template <typename... Ts>
typename list<T>::iterator list<T>::insert_many(const iterator c_pos,
                                                Ts&&... vals) {
  iterator pos = c_pos;

  if constexpr (sizeof...(vals) > 0) {
    size_t j = 0;

    for (const auto it : {vals...})
      if (j++ != sizeof...(vals) - 1)
        insert(pos, it);
      else
        pos = insert(pos, it);

    for (size_type i = 0; i != sizeof...(vals); ++i) --pos;
  }

  return pos;
}

template <typename T>
template <typename... Ts>
void list<T>::insert_many_front(Ts&&... vals) {
  insert_many(begin(), vals...);
}

template <typename T>
template <typename... Ts>
void list<T>::insert_many_back(Ts&&... vals) {
  (push_back(value_type(std::forward<Ts>(vals))), ...);
}

}  // namespace s21
#endif  // SRC_LIST_H_