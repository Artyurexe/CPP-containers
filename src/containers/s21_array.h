#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include "../s21_containers.h"

// using namespace std;
namespace s21 {

template <typename T, size_t Size>
class s21_array {
 public:
  // Member type definitions
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;

  // Constructors and destructor
  s21_array() = default;
  s21_array(std::initializer_list<T> const& items);
  s21_array(const s21_array& other);
  s21_array(s21_array&& other) noexcept;
  ~s21_array();

  // Assignment operator overload
  s21_array& operator=(s21_array&& other) noexcept;

  // Element access methods
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Iterator methods
  iterator begin();
  iterator end();

  // Capacity methods
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void swap(s21_array& other);
  void fill(const_reference value);

 private:
  T elements[Size];
};

template <typename T, size_t Size>
s21_array<T, Size>::s21_array(std::initializer_list<T> const& items) {
  if (items.size() != Size) {
    throw std::invalid_argument("Pass wrong argumet for s21_array");
  }
  size_type i = 0;
  for (const auto& item : items) {
    elements[i++] = item;
  }
}

template <typename T, size_t Size>
s21_array<T, Size>::s21_array(const s21_array& other) {
  for (size_type i = 0; i < Size; ++i) {
    elements[i] = other.elements[i];
  }
}

template <typename T, size_t Size>
s21_array<T, Size>::s21_array(s21_array&& other) noexcept {
  for (size_type i = 0; i < other.size(); ++i) {
    elements[i] = std::move(other.elements[i]);
  }
}

// Destructor
template <typename T, size_t Size>
s21_array<T, Size>::~s21_array() {}

// Move assignment operator
template <typename T, size_t Size>
s21_array<T, Size>& s21_array<T, Size>::operator=(s21_array&& other) noexcept {
  if (this != &other) {
    for (size_type i = 0; i < Size; ++i) {
      elements[i] = std::move(other.elements[i]);
    }
  }
  return *this;
}

// Element access methods
template <typename T, size_t Size>
typename s21_array<T, Size>::reference s21_array<T, Size>::at(size_type pos) {
  if (pos >= Size) {
    throw std::out_of_range("Array index out of bounds");
  }
  return elements[pos];
}

template <typename T, size_t Size>
typename s21_array<T, Size>::reference s21_array<T, Size>::operator[](
    size_type pos) {
  return elements[pos];
}

template <typename T, size_t Size>
typename s21_array<T, Size>::const_reference s21_array<T, Size>::front() {
  return elements[0];
}

template <typename T, size_t Size>
typename s21_array<T, Size>::const_reference s21_array<T, Size>::back() {
  return elements[Size - 1];
}

template <typename T, size_t Size>
typename s21_array<T, Size>::iterator s21_array<T, Size>::data() {
  return elements;
}

// Iterator methods
template <typename T, size_t Size>
typename s21_array<T, Size>::iterator s21_array<T, Size>::begin() {
  return elements;
}

template <typename T, size_t Size>
typename s21_array<T, Size>::iterator s21_array<T, Size>::end() {
  return elements + Size;
}

// Capacity methods
template <typename T, size_t Size>
bool s21_array<T, Size>::empty() const {
  return Size == 0;
}

template <typename T, size_t Size>
typename s21_array<T, Size>::size_type s21_array<T, Size>::size() const {
  return Size;
}

template <typename T, size_t Size>
typename s21_array<T, Size>::size_type s21_array<T, Size>::max_size() const {
  return Size;
}

// Modifiers
template <typename T, size_t Size>
void s21_array<T, Size>::swap(s21_array& other) {
  std::swap(elements, other.elements);
}

template <typename T, size_t Size>
void s21_array<T, Size>::fill(const_reference value) {
  for (size_type i = 0; i < Size; ++i) {
    elements[i] = value;
  }
}
}  // namespace s21

#endif