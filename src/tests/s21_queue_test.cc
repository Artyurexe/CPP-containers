#include <gtest/gtest.h>

#include <utility>

#include "s21_containers.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> queue;

  EXPECT_EQ(0U, queue.size());
}

TEST(QueueTest, InitListConstructor) {
  s21::queue<unsigned> queue({10, 11, 12, 13, 14});

  EXPECT_EQ(5U, queue.size());

  for (size_t i = 10; i < 15; ++i) {
    EXPECT_EQ(queue.front(), i);
    queue.pop();
  }
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<double> queue1({0.0, 0.1, 0.2, 0.3, 0.4});
  s21::queue<double> queue2(queue1);

  EXPECT_EQ(5U, queue2.size());

  while (!queue2.empty()) {
    EXPECT_DOUBLE_EQ(queue1.front(), queue2.front());
    queue1.pop();
    queue2.pop();
  }
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<double> queue1({0.0, 0.1, 0.2, 0.3, 0.4});
  s21::queue<double> queue2(std::move(queue1));

  EXPECT_EQ(0U, queue1.size());
  EXPECT_EQ(5U, queue2.size());

  for (size_t i = 0; i != 5; ++i) {
    EXPECT_DOUBLE_EQ(queue2.front(), i / 10.);
    queue2.pop();
  }
}

TEST(QueueTest, MoveAssignment) {
  s21::queue<int> queue1;
  s21::queue<int> queue2({100, 200, 300});

  queue1 = std::move(queue2);

  EXPECT_EQ(3U, queue1.size());
  EXPECT_EQ(0U, queue2.size());

  for (int i = 100; i < 400; i += 100) {
    EXPECT_EQ(queue1.front(), i);
    queue1.pop();
  }
}

TEST(QueueTest, Front) {
  s21::queue<double> queue({0.0, 0.1, 0.2, 0.3, 0.4});

  EXPECT_DOUBLE_EQ(queue.front(), 0.0);
}

TEST(QueueTest, Back) {
  s21::queue<int> queue({5, 4, 3, 2, 1, 0, 999});

  EXPECT_EQ(999, queue.back());
}

TEST(QueueTest, Empty) {
  s21::queue<double> queue({0.0});

  EXPECT_EQ(queue.empty(), false);

  queue.pop();

  EXPECT_EQ(queue.empty(), true);
}

TEST(QueueTest, PushPop) {
  s21::queue<uint> queue({0});

  queue.push(1);
  queue.push(2);
  queue.push(3);

  EXPECT_EQ(4U, queue.size());

  for (size_t i = 0; i < queue.size(); ++i) {
    EXPECT_EQ(queue.front(), i);
    queue.pop();
  }
}

TEST(QueueTest, Swap) {
  s21::queue<uint> queue1({0, 1, 2, 3});
  s21::queue<uint> queue2({100, 101, 102, 103});

  queue1.swap(queue2);

  EXPECT_EQ(4U, queue1.size());
  EXPECT_EQ(4U, queue2.size());

  for (size_t i = 0; i < queue1.size(); ++i) {
    EXPECT_EQ(queue1.front(), i + 100);
    queue1.pop();
  }

  for (size_t i = 0; i < queue2.size(); ++i) {
    EXPECT_EQ(queue2.front(), i);
    queue2.pop();
  }
}

TEST(QueueTest, SwapEmptySource) {
  s21::queue<uint> queue1({0, 1, 2, 3});
  s21::queue<uint> queue2;

  queue1.swap(queue2);

  EXPECT_EQ(0U, queue1.size());
  EXPECT_EQ(4U, queue2.size());

  for (size_t i = 0; i < queue2.size(); ++i) {
    EXPECT_EQ(queue2.front(), i);
    queue2.pop();
  }
}

TEST(QueueTest, SwapEmptyTarget) {
  s21::queue<uint> queue1;
  s21::queue<uint> queue2({100, 101, 102, 103});

  queue1.swap(queue2);

  EXPECT_EQ(4U, queue1.size());
  EXPECT_EQ(0U, queue2.size());

  for (size_t i = 0; i < queue1.size(); ++i) {
    EXPECT_EQ(queue1.front(), i + 100);
    queue1.pop();
  }
}

TEST(QueueTest, SwapEmptyEmpty) {
  s21::queue<uint> queue1;
  s21::queue<uint> queue2;

  queue1.swap(queue2);

  EXPECT_EQ(0U, queue1.size());
  EXPECT_EQ(0U, queue2.size());
}

TEST(QueueTest, InsertManyFront) {
  s21::queue<uint> queue({0, 1});

  queue.insert_many_back(2, 3, 4, 5, 6, 7, 8);

  EXPECT_EQ(9U, queue.size());

  for (size_t i = 0; i < queue.size(); ++i) {
    EXPECT_EQ(queue.front(), i);
    queue.pop();
  }
}