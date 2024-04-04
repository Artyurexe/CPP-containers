#include <gtest/gtest.h>

#include <utility>

#include "s21_containers.h"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> list;

  EXPECT_EQ(0U, list.size());
}

TEST(ListTest, nConstructor) {
  s21::list<uint> list(9);

  EXPECT_EQ(9U, list.size());
}

TEST(ListTest, nOfValConstructor) {
  s21::list<char> list(3, 'd');

  EXPECT_EQ(3U, list.size());

  for (auto it : list) EXPECT_EQ(it, 'd');
}

TEST(ListTest, InitListConstructor) {
  s21::list<unsigned> list({10, 11, 12, 13, 14});

  EXPECT_EQ(5U, list.size());

  auto it = list.begin();
  for (size_t i = 10; i < 15; ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, CopyConstructor) {
  s21::list<double> list1({0.0, 0.1, 0.2, 0.3, 0.4});
  s21::list<double> list2(list1);

  EXPECT_EQ(5U, list2.size());

  auto it1 = list1.begin();
  auto it2 = list2.begin();
  for (size_t i = 0; i < list1.size(); ++i)
    EXPECT_DOUBLE_EQ(*(it1++), *(it2++));
}

TEST(ListTest, MoveConstructor) {
  s21::list<double> list1({0.0, 0.1, 0.2, 0.3, 0.4});
  s21::list<double> list2(std::move(list1));

  EXPECT_EQ(0U, list1.size());
  EXPECT_EQ(5U, list2.size());

  auto it = list2.begin();
  for (size_t i = 0; i < list1.size(); ++i) EXPECT_DOUBLE_EQ(*(it++), i / 10.);
}

TEST(ListTest, CopyAssignment) {
  s21::list<int> list1;
  s21::list<int> list2({100, 200, 300});

  list1 = list2;

  EXPECT_EQ(list1.size(), list2.size());

  for (auto it1 = list1.cbegin(), it2 = list2.cbegin(); it1 != list1.cend();
       ++it1)
    EXPECT_EQ(*it1, *(it2++));
}

TEST(ListTest, MoveAssignment) {
  s21::list<int> list1;
  s21::list<int> list2({100, 200, 300});

  list1 = std::move(list2);

  EXPECT_EQ(3U, list1.size());
  EXPECT_EQ(0U, list2.size());

  auto it1 = list1.cbegin();
  for (int i = 100; i < 400; i += 100) EXPECT_EQ(*(it1++), i);
}

TEST(ListTest, Front) {
  s21::list<double> list({0.0, 0.1, 0.2, 0.3, 0.4});

  EXPECT_DOUBLE_EQ(list.front(), 0.0);
}

TEST(ListTest, Back) {
  s21::list<double> list({0.0, 0.1, 0.2, 0.3, 0.4});

  EXPECT_DOUBLE_EQ(list.back(), 0.4);
}

TEST(ListTest, Begin) {
  s21::list<double> list({0.0, 0.1, 0.2, 0.3, 0.4});

  *(list.begin()) = -1.0;

  EXPECT_DOUBLE_EQ(*(list.begin()), -1.0);
}

TEST(ListTest, CBegin) {
  s21::list<double> list({0.0, 0.1, 0.2, 0.3, 0.4});

  EXPECT_DOUBLE_EQ(*(list.cbegin()), 0.0);
}

TEST(ListTest, ClearEmpty) {
  s21::list<char> list{'c', 'l', 'e', 'a', 'r'};

  EXPECT_EQ(5U, list.size());
  EXPECT_EQ(false, list.empty());

  list.clear();

  EXPECT_EQ(0U, list.size());
  EXPECT_EQ(true, list.empty());
}

TEST(ListTest, InsertBegin) {
  s21::list<uint> list({1, 2, 3});

  list.insert(list.begin(), 0);

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, InsertEnd) {
  s21::list<uint> list({0, 1, 2});

  list.insert(list.end(), 3);

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, InsertMid) {
  s21::list<uint> list({0, 1, 3});

  auto it = list.begin();
  ++it;
  ++it;
  list.insert(it, 2);

  EXPECT_EQ(4U, list.size());

  it = list.begin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, Erase) {
  s21::list<uint> list({0, 1, 2, 3});

  EXPECT_EQ(4U, list.size());

  auto it = list.begin();
  ++it;
  ++it;
  list.erase(it);

  EXPECT_EQ(3U, list.size());

  it = list.begin();
  for (size_t i = 0; i < list.size(); ++i) {
    if (i == 2) ++i;
    EXPECT_EQ(*(it++), i);
  }
}

TEST(ListTest, PushFront) {
  s21::list<uint> list({1, 2, 3});

  list.push_front(0);

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, PushBack) {
  s21::list<uint> list({0, 1, 2});

  list.push_back(3);

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, PoopFront) {
  s21::list<uint> list({999, 0, 1, 2, 3});

  list.pop_front();

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, PoopBack) {
  s21::list<uint> list({0, 1, 2, 3, 999});

  list.pop_back();

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, Swap) {
  s21::list<uint> list1({0, 1, 2, 3});
  s21::list<uint> list2({100, 101, 102, 103});

  list1.swap(list2);

  EXPECT_EQ(4U, list1.size());
  EXPECT_EQ(4U, list2.size());

  auto it = list1.cbegin();
  for (size_t i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i + 100);

  it = list2.cbegin();
  for (size_t i = 0; i < list2.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SwapEmptySource) {
  s21::list<uint> list1({0, 1, 2, 3});
  s21::list<uint> list2;

  list1.swap(list2);

  EXPECT_EQ(0U, list1.size());
  EXPECT_EQ(4U, list2.size());

  auto it = list2.cbegin();
  for (size_t i = 0; i < list2.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SwapEmptyTarget) {
  s21::list<uint> list1;
  s21::list<uint> list2({0, 1, 2, 3});

  list1.swap(list2);

  EXPECT_EQ(4U, list1.size());
  EXPECT_EQ(0U, list2.size());

  auto it = list1.cbegin();
  for (size_t i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SwapEmptyEmpty) {
  s21::list<uint> list1;
  s21::list<uint> list2;

  list1.swap(list2);

  EXPECT_EQ(0U, list1.size());
  EXPECT_EQ(0U, list2.size());
}

TEST(ListTest, Reverse) {
  s21::list<char> list({'d', 'c', 'b', 'a'});

  list.reverse();

  auto it = list.cbegin();
  for (char i = 'a'; i < 'e'; ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, ReverseEmpty) {
  s21::list<char> list;

  list.reverse();

  EXPECT_EQ(0U, list.size());
}

TEST(ListTest, Sort) {
  s21::list<uint> list({7, 3, 0, 2, 9, 4, 8, 6, 1, 5});

  list.sort();

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SortEmpty) {
  s21::list<uint> list;

  list.sort();

  EXPECT_EQ(0U, list.size());
}

TEST(ListTest, Unique) {
  s21::list<uint> list({0, 0, 0, 0, 1, 1, 2, 3, 3, 3, 3, 3});

  list.unique();

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, UniqueUniqued) {
  s21::list<uint> list({0, 0, 0, 0, 1, 1, 2, 3, 3, 3, 3, 3});

  list.unique();
  list.unique();

  EXPECT_EQ(4U, list.size());

  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, Merge) {
  s21::list<uint> list1({7, 3, 0, 5});
  s21::list<uint> list2({2, 9, 4, 8, 6, 1});

  list1.merge(list2);

  EXPECT_EQ(10U, list1.size());

  auto it = list1.cbegin();
  for (size_t i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, MergeEmptySource) {
  s21::list<uint> list1({3, 1, 0, 2});
  s21::list<uint> list2;

  list1.merge(list2);

  EXPECT_EQ(4U, list1.size());

  auto it = list1.cbegin();
  for (size_t i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, MergeEmptyTarget) {
  s21::list<uint> list1;
  s21::list<uint> list2({3, 1, 0, 2});

  list1.merge(list2);

  EXPECT_EQ(4U, list1.size());

  auto it = list1.cbegin();
  for (size_t i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, Splice) {
  s21::list<uint> list1({0, 9});
  s21::list<uint> list2({1, 2, 3, 4, 5, 6, 7, 8});

  auto it = list1.begin();
  ++it;
  list1.splice(it, list2);

  EXPECT_EQ(10U, list1.size());

  it = list1.begin();
  for (uint i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SpliceEnd) {
  s21::list<uint> list1({0, 1});
  s21::list<uint> list2({2, 3, 4, 5, 6, 7, 8, 9});

  list1.splice(list1.end(), list2);

  EXPECT_EQ(10U, list1.size());

  auto it = list1.begin();
  for (uint i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SpliceBegin) {
  s21::list<uint> list1({9});
  s21::list<uint> list2({0, 1, 2, 3, 4, 5, 6, 7, 8});

  list1.splice(list1.begin(), list2);

  EXPECT_EQ(10U, list1.size());

  auto it = list1.begin();
  for (uint i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SpliceEmpty) {
  s21::list<uint> list1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::list<uint> list2;

  auto it = list1.begin();
  ++it;
  list1.splice(it, list2);

  EXPECT_EQ(10U, list1.size());

  it = list1.begin();
  for (uint i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, SpliceToEmpty) {
  s21::list<uint> list1;
  s21::list<uint> list2({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

  list1.splice(list1.begin(), list2);

  EXPECT_EQ(10U, list1.size());

  auto it = list1.begin();
  for (uint i = 0; i < list1.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, InsertMany) {
  s21::list<uint> list({0, 9});

  auto it = list.begin();
  ++it;
  list.insert_many(it, 1, 2, 3, 4, 5, 6, 7, 8);

  EXPECT_EQ(10U, list.size());

  it = list.begin();
  for (uint i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, InsertManyToEmpty) {
  s21::list<uint> list;

  auto it = list.begin();
  list.insert_many(it, 0, 1, 2, 3, 4, 5, 6, 7, 8);

  EXPECT_EQ(9U, list.size());

  it = list.begin();
  for (uint i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, InsertManyNone) {
  s21::list<uint> list({0, 1, 2});

  auto it = list.begin();
  ++it;
  list.insert_many(it);

  EXPECT_EQ(3U, list.size());

  it = list.begin();
  for (uint i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, InsertManyNoneToEmpty) {
  s21::list<uint> list;

  list.insert_many(list.begin());

  EXPECT_EQ(0U, list.size());
}

TEST(ListTest, InsertManyFront) {
  s21::list<uint> list({7, 8});

  list.insert_many_front(0, 1, 2, 3, 4, 5, 6);

  EXPECT_EQ(9U, list.size());

  auto it = list.begin();
  for (uint i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}

TEST(ListTest, InsertManyBack) {
  s21::list<uint> list({0, 1});

  list.insert_many_back(2, 3, 4, 5, 6, 7, 8);

  EXPECT_EQ(9U, list.size());

  auto it = list.begin();
  for (uint i = 0; i < list.size(); ++i) EXPECT_EQ(*(it++), i);
}
