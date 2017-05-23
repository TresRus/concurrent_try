#include <thread>
#include <iostream>

#include "utils/stack/locked.h"
#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

TEST(LockStackTest, EmptyAtStart) { 
    stack::Locked<int> stack;
    ASSERT_TRUE(stack.Empty());
}

TEST(LockStackTest, PushOne) { 
    stack::Locked<int> stack;
    stack.Push(1);
    ASSERT_FALSE(stack.Empty());
}

TEST(LockStackTest, PushPop) { 
    stack::Locked<int> stack;
    stack.Push(1);
    ASSERT_FALSE(stack.Empty());

    auto value = stack.Pop();
    ASSERT_TRUE(stack.Empty());
    ASSERT_EQ(*value, 1);
}

TEST(LockStackTest, PopEmpty) { 
    stack::Locked<int> stack;

    auto value = stack.Pop();
    ASSERT_TRUE(stack.Empty());
    ASSERT_EQ(value, nullptr);
}

void Push(stack::Locked<int>& stack, int max_value) {
    for (int i = 0; i < max_value; ++i)
        stack.Push(i);
}

void Pop(stack::Locked<int>& stack, int max_value) {
    for (int i = 0; i < max_value; ++i) {
        auto value = stack.Pop();
        ASSERT_NE(value, nullptr);
    }
}

TEST(LockStackTest, PushPopParallel) {
    stack::Locked<int> stack;
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

} // namespace utils
} // namespace concurent
