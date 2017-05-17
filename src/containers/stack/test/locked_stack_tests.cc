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
