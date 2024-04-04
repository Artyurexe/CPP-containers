#include <gtest/gtest.h>

#include <utility>

#include "s21_containers.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> stack;

  EXPECT_EQ(0U, stack.size());
}

TEST(StackTest, InitListConstructor) {
  s21::stack<unsigned> stack({10, 11, 12, 13, 14});

  EXPECT_EQ(5U, stack.size());

  for (size_t i = 14; i > 9; --i) {
    EXPECT_EQ(stack.top(), i);
    stack.pop();
  }
}

TEST(StackTest, CopyConstructor) {
  s21::stack<double> stack1({0.0, 0.1, 0.2, 0.3, 0.4});
  s21::stack<double> stack2(stack1);

  EXPECT_EQ(5U, stack2.size());

  while (!stack2.empty()) {
    EXPECT_DOUBLE_EQ(stack1.top(), stack2.top());
    stack1.pop();
    stack2.pop();
  }
}

TEST(StackTest, MoveConstructor) {
  s21::stack<double> stack1({0.0, 0.1, 0.2, 0.3, 0.4});
  s21::stack<double> stack2(std::move(stack1));

  EXPECT_EQ(0U, stack1.size());
  EXPECT_EQ(5U, stack2.size());

  for (size_t i = 5; i != 0; --i) {
    EXPECT_DOUBLE_EQ(stack2.top(), (i - 1) / 10.);
    stack2.pop();
  }
}

TEST(StackTest, MoveAssignment) {
  s21::stack<int> stack1;
  s21::stack<int> stack2({300, 200, 100});

  stack1 = std::move(stack2);

  EXPECT_EQ(3U, stack1.size());
  EXPECT_EQ(0U, stack2.size());

  for (int i = 100; i < 400; i += 100) {
    EXPECT_EQ(stack1.top(), i);
    stack1.pop();
  }
}

TEST(StackTest, Top) {
  s21::stack<double> stack({0.0, 0.1, 0.2, 0.3, 0.4});

  EXPECT_DOUBLE_EQ(stack.top(), 0.4);
}

TEST(StackTest, Empty) {
  s21::stack<double> stack({0.0});

  EXPECT_EQ(stack.empty(), false);

  stack.pop();

  EXPECT_EQ(stack.empty(), true);
}

TEST(StackTest, PushPop) {
  s21::stack<uint> stack({3});

  stack.push(2);
  stack.push(1);
  stack.push(0);

  EXPECT_EQ(4U, stack.size());

  for (size_t i = 0; i < stack.size(); ++i) {
    EXPECT_EQ(stack.top(), i);
    stack.pop();
  }
}

TEST(StackTest, Swap) {
  s21::stack<uint> stack1({3, 2, 1, 0});
  s21::stack<uint> stack2({103, 102, 101, 100});

  stack1.swap(stack2);

  EXPECT_EQ(4U, stack1.size());
  EXPECT_EQ(4U, stack2.size());

  for (size_t i = 0; i < stack1.size(); ++i) {
    EXPECT_EQ(stack1.top(), i + 100);
    stack1.pop();
  }

  for (size_t i = 0; i < stack2.size(); ++i) {
    EXPECT_EQ(stack2.top(), i);
    stack2.pop();
  }
}

TEST(StackTest, SwapEmptySource) {
  s21::stack<uint> stack1({3, 2, 1, 0});
  s21::stack<uint> stack2;

  stack1.swap(stack2);

  EXPECT_EQ(0U, stack1.size());
  EXPECT_EQ(4U, stack2.size());

  for (size_t i = 0; i < stack2.size(); ++i) {
    EXPECT_EQ(stack2.top(), i);
    stack2.pop();
  }
}

TEST(StackTest, SwapEmptyTarget) {
  s21::stack<uint> stack1;
  s21::stack<uint> stack2({103, 102, 101, 100});

  stack1.swap(stack2);

  EXPECT_EQ(4U, stack1.size());
  EXPECT_EQ(0U, stack2.size());

  for (size_t i = 0; i < stack1.size(); ++i) {
    EXPECT_EQ(stack1.top(), i + 100);
    stack1.pop();
  }
}

TEST(StackTest, SwapEmptyEmpty) {
  s21::stack<uint> stack1;
  s21::stack<uint> stack2;

  stack1.swap(stack2);

  EXPECT_EQ(0U, stack1.size());
  EXPECT_EQ(0U, stack2.size());
}

TEST(StackTest, InsertManyFront) {
  s21::stack<uint> stack({8, 7});

  stack.insert_many_front(6, 5, 4, 3, 2, 1, 0);

  EXPECT_EQ(9U, stack.size());

  for (size_t i = 0; i < stack.size(); ++i) {
    EXPECT_EQ(stack.top(), i);
    stack.pop();
  }
}