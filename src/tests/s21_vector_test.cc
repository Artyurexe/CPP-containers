#include <gtest/gtest.h>

#include <iostream>
#include <utility>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

TEST(VectorTest, DefaultConstructor) {
  s21::s21_vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, ParameterizedConstructor) {
  s21::s21_vector<int> s21_v(4);
  std::vector<int> std_v(4);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, InitializerListConstructor) {
  s21::s21_vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  EXPECT_EQ(s21_v.size(), std_v.size());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, CopyConstructor) {
  s21::s21_vector<int> s21_v1 = {1, 2, 3};
  s21::s21_vector<int> s21_v2(s21_v1);
  //   std::vector<int> std_v1 = {1, 2, 3};
  //   std::vector<int> std_v2(std_v1);
  EXPECT_EQ(s21_v1.size(), s21_v2.size());
  for (size_t i = 0; i < s21_v1.size(); ++i) {
    EXPECT_EQ(s21_v1[i], s21_v2[i]);
    // EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
}

TEST(VectorTest, MoveConstructor) {
  s21::s21_vector<int> s21_v1 = {1, 2, 3};
  s21::s21_vector<int> s21_v2 = std::move(s21_v1);
  std::vector<int> std_v1 = {1, 2, 3};
  std::vector<int> std_v2 = std::move(std_v1);
  EXPECT_EQ(s21_v1.size(), static_cast<size_t>(0));
  EXPECT_EQ(std_v1.size(), static_cast<size_t>(0));
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
}

TEST(VectorTest, Insert) {
  s21::s21_vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  auto s21_it = s21_v.insert(s21_v.begin() + 1, 4);
  auto std_it = std_v.insert(std_v.begin() + 1, 4);

  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_v.size(), std_v.size());

  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, Erase) {
  s21::s21_vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.erase(s21_v.begin() + 1);
  std_v.erase(std_v.begin() + 1);

  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, PushBack) {
  s21::s21_vector<int> s21_v;
  std::vector<int> std_v;

  for (int i = 1; i <= 3; ++i) {
    s21_v.push_back(i);
    std_v.push_back(i);

    EXPECT_EQ(s21_v.size(), std_v.size());
    EXPECT_EQ(s21_v.back(), std_v.back());
  }
}

TEST(VectorTest, PopBack) {
  s21::s21_vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  for (int i = 3; i >= 1; --i) {
    s21_v.pop_back();
    std_v.pop_back();

    EXPECT_EQ(s21_v.size(), std_v.size());
  }

  EXPECT_TRUE(s21_v.empty());
  EXPECT_TRUE(std_v.empty());
}

TEST(VectorTest, Swap) {
  s21::s21_vector<int> s21_v1 = {1, 2, 3};
  s21::s21_vector<int> s21_v2 = {4, 5};
  std::vector<int> std_v1 = {1, 2, 3};
  std::vector<int> std_v2 = {4, 5};
  size_t s21_v1_size_before_swap = s21_v1.size();
  size_t s21_v2_size_before_swap = s21_v2.size();

  s21_v1.swap(s21_v2);

  EXPECT_EQ(s21_v1.size(), s21_v2_size_before_swap);
  EXPECT_EQ(s21_v2.size(), s21_v1_size_before_swap);

  auto it1 = s21_v1.begin();
  auto it2 = s21_v2.begin();
  auto it3 = std_v1.begin();
  auto it4 = std_v2.begin();

  while (it1 != s21_v1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }

  while (it2 != s21_v2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
}

/// Bonus

TEST(VectorTest, InsertMany) {
  s21::s21_vector<int> s21_v = {1, 2, 3};
  s21::s21_vector<int> std_v = {1, 4, 5, 6, 2, 3};

  s21_v.insert_many(s21_v.begin() + 1, 4, 5, 6);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v[0], 1);
  EXPECT_EQ(s21_v[1], 4);
  EXPECT_EQ(s21_v[2], 5);
  EXPECT_EQ(s21_v[3], 6);
  EXPECT_EQ(s21_v[4], 2);
  EXPECT_EQ(s21_v[5], 3);
}
