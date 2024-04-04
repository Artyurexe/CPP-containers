#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class s21_vector {
 public:
  typedef size_t size_type;
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;

 public:
  // constructors & destructor
  s21_vector();
  explicit s21_vector(size_type n);
  s21_vector(std::initializer_list<T> const& item);
  s21_vector(const s21_vector& other);
  s21_vector(s21_vector&& other) noexcept;
  ~s21_vector();

  // operator
  s21_vector& operator=(s21_vector&& other) noexcept;

  // element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;

  // iterators
  iterator begin();
  iterator end();

  // capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type new_capacity);
  size_type capacity() const;
  void shrink_to_fit();

  T* data();

  // modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(s21_vector& other);

  // bonus
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  T* v_data;
  size_type v_size;
  size_type v_capacity;
};

template <typename T>
s21_vector<T>::s21_vector() : v_data(nullptr), v_size(0), v_capacity(0) {}

template <typename T>
s21_vector<T>::~s21_vector() {
  clear();
  delete[] v_data;
}

template <typename T>
s21_vector<T>::s21_vector(size_type n)
    : v_data(new T[n]), v_size(n), v_capacity(n) {
  std::uninitialized_fill(v_data, v_data + v_size, T());
}

template <typename T>
s21_vector<T>::s21_vector(std::initializer_list<T> const& items)
    : v_data(new T[items.size()]),
      v_size(items.size()),
      v_capacity(items.size()) {
  std::uninitialized_copy(items.begin(), items.end(), v_data);
}

template <typename T>
s21_vector<T>::s21_vector(const s21_vector& other)
    : v_data(new T[other.v_capacity]),
      v_size(other.v_size),
      v_capacity(other.v_capacity) {
  std::uninitialized_copy(other.v_data, other.v_data + other.v_size, v_data);
}

template <typename T>
s21_vector<T>::s21_vector(s21_vector&& other) noexcept
    : v_data(other.v_data), v_size(other.v_size), v_capacity(other.v_capacity) {
  other.v_data = nullptr;
  other.v_size = 0;
  other.v_capacity = 0;
}

template <typename T>
s21_vector<T>& s21_vector<T>::operator=(s21_vector&& other) noexcept {
  if (this != &other) {
    clear();
    delete[] v_data;
    v_data = other.v_data;
    v_size = other.v_size;
    v_capacity = other.v_capacity;

    other.v_data = nullptr;
    other.v_size = 0;
    other.v_capacity = 0;
  }
  return *this;
}

// element access
template <typename T>
typename s21_vector<T>::reference s21_vector<T>::at(size_type pos) {
  if (pos >= v_size) {
    throw std::out_of_range("Index out of range");
  }
  return v_data[pos];
}

template <typename T>
typename s21_vector<T>::reference s21_vector<T>::operator[](size_type pos) {
  return v_data[pos];
}

template <typename T>
typename s21_vector<T>::const_reference s21_vector<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Front() on empty vector");
  }
  return v_data[0];
}

template <typename T>
typename s21_vector<T>::const_reference s21_vector<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Back() on empty vector");
  }
  return v_data[v_size - 1];
}

template <typename T>
T* s21_vector<T>::data() {
  return v_data;
}

// iterators
template <typename T>
typename s21_vector<T>::iterator s21_vector<T>::begin() {
  return v_data;
}

template <typename T>
typename s21_vector<T>::iterator s21_vector<T>::end() {
  return v_data + v_size;
}

// capacity
template <typename T>
bool s21_vector<T>::empty() const {
  return v_size == 0;
}

template <typename T>
typename s21_vector<T>::size_type s21_vector<T>::size() const {
  return v_size;
}

template <typename T>
typename s21_vector<T>::size_type s21_vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
typename s21_vector<T>::size_type s21_vector<T>::capacity() const {
  return v_capacity;
}

template <typename T>
void s21_vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > v_capacity) {
    T* new_data = new T[new_capacity];
    std::uninitialized_copy(v_data, v_data + v_size, new_data);
    delete[] v_data;
    v_data = new_data;
    v_capacity = new_capacity;
  }
}

template <typename T>
void s21_vector<T>::shrink_to_fit() {
  if (v_capacity > v_size) {
    T* new_data = new T[v_size];
    std::uninitialized_copy(v_data, v_data + v_size, new_data);
    delete[] v_data;
    v_data = new_data;
    v_capacity = v_size;
  }
}

// modifiers
template <typename T>
void s21_vector<T>::clear() {
  for (size_type i = 0; i < v_size; ++i) {
    v_data[i].~T();
  }
  v_size = 0;
}

template <typename T>
typename s21_vector<T>::iterator s21_vector<T>::insert(iterator pos,
                                                       const_reference value) {
  size_type index = pos - begin();
  if (index > v_size) {
    throw std::out_of_range("Insert() - out of range");
  }
  if (v_size == v_capacity) {
    reserve(v_capacity == 0 ? 1 : v_capacity * 2);
  }
  for (size_type i = v_size; i > index; --i) {
    new (v_data + i) T(std::move(v_data[i - 1]));
  }
  new (v_data + index) T(value);
  ++v_size;
  return begin() + index;
}

template <typename T>
void s21_vector<T>::erase(iterator pos) {
  size_type index = pos - begin();
  if (index >= v_size) {
    throw std::out_of_range("s21_vector::erase() - iterator out of range");
  }
  v_data[index].~T();
  for (size_type i = index; i < v_size - 1; ++i) {
    v_data[i] = std::move(v_data[i + 1]);
  }
  --v_size;
}

template <typename T>
void s21_vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void s21_vector<T>::pop_back() {
  if (v_size > 0) {
    erase(end() - 1);
  }
}

template <typename T>
void s21_vector<T>::swap(s21_vector& other) {
  std::swap(v_data, other.v_data);
  std::swap(v_size, other.v_size);
  std::swap(v_capacity, other.v_capacity);
}

}  // namespace s21

#endif  // S21_VECTOR_H
