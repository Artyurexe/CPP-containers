#ifndef S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_H_
#define S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_H_

//============Bonus vector===========//
namespace s21 {
// template <typename T>
// template <typename... Args>
// typename s21_vector<T>::iterator s21_vector<T>::insert_many(const_iterator
// pos,
//                                                             Args&&... args) {
//   size_type index = pos - begin();

//   if (index > v_size) {
//     throw std::out_of_range("Insert_many() is out of range");
//   }

//   size_type numArgs = sizeof...(args);
//   size_type new_capacity = v_size + numArgs;
//   if (new_capacity > v_capacity) {
//     reserve(new_capacity);
//   }

//   size_type i = index;
//   ((void)(v_data[i++] = std::forward<Args>(args)), ...);

//   v_size += numArgs;

//   return begin() + index;
// }

// template <typename T>
// template <typename... Args>
// void s21_vector<T>::insert_many_back(Args&&... args) {
//
// }

template <typename T>
template <typename... Args>
inline typename s21_vector<T>::iterator s21_vector<T>::insert_many(
    const_iterator pos, Args &&...args) {
  s21::s21_vector<value_type> tmp{args...};
  iterator position = (iterator)pos;
  for (size_t i = 0; i < tmp.size(); ++i) {
    position = insert(position, tmp[i]) + 1;
  }
  return position;
}

template <typename T>
template <typename... Args>
inline void s21_vector<T>::insert_many_back(Args &&...args) {
  insert_many(end(), std::forward<Args>(args)...);
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_H_
