#include <thread>
#include <iostream>

#include "containers/stack/stack.h"
#include "gtest/gtest.h"

TEST(LockStackTest, EmptyAtStart) { 
    concurrent::containers::Stack<int> stack;
    ASSERT_TRUE(stack.Empty());
}

TEST(LockStackTest, PushOne) { 
    concurrent::containers::Stack<int> stack;
    stack.Push(1);
    ASSERT_FALSE(stack.Empty());
}

TEST(LockStackTest, PushPop) { 
    concurrent::containers::Stack<int> stack;
    stack.Push(1);
    ASSERT_FALSE(stack.Empty());

    auto value = stack.Pop();
    ASSERT_TRUE(stack.Empty());
    ASSERT_EQ(*value, 1);
}

TEST(LockStackTest, PopEmpty) { 
    concurrent::containers::Stack<int> stack;

    auto value = stack.Pop();
    ASSERT_TRUE(stack.Empty());
    ASSERT_EQ(value, nullptr);
}

void Push(concurrent::containers::Stack<int>& stack, int max_value) {
    for (int i = 0; i < max_value; ++i)
        stack.Push(i);
}

void Pop(concurrent::containers::Stack<int>& stack, int max_value) {
    for (int i = 0; i < max_value; ++i) {
        auto value = stack.Pop();
        ASSERT_NE(value, nullptr);
    }
}

TEST(LockStackTest, PushPopParallel) {
    concurrent::containers::Stack<int> stack;
    const int max_value = 10000;

    std::thread t1(Push, std::ref(stack), max_value);
    Push(stack, max_value);
    t1.join();

    ASSERT_FALSE(stack.Empty());

    std::thread t2(Pop, std::ref(stack), max_value);
    Pop(stack, max_value);
    t2.join();

    ASSERT_TRUE(stack.Empty());
}
