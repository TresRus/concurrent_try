#include <thread>

#include "utils/queue/locked.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

TEST(LockQueueTest, EmptyAtStart) { 
    queue::Locked<int> queue;
    ASSERT_TRUE(queue.Empty());
}

TEST(LockQueueTest, PushOne) { 
    queue::Locked<int> queue;
    queue.Push(1);
    ASSERT_FALSE(queue.Empty());
}

TEST(LockQueueTest, PushPop) { 
    queue::Locked<int> queue;
    queue.Push(1);
    ASSERT_FALSE(queue.Empty());

    auto value = queue.TryPop();
    ASSERT_TRUE(queue.Empty());
    ASSERT_EQ(*value, 1);
}

TEST(LockQueueTest, PopEmpty) { 
    queue::Locked<int> queue;

    auto value = queue.TryPop();
    ASSERT_TRUE(queue.Empty());
    ASSERT_EQ(value, nullptr);
}

void Push(queue::Locked<int>& queue, int max_value) {
    for (int i = 0; i < max_value; ++i)
        queue.Push(i);
}

void Pop(queue::Locked<int>& queue, int max_value) {
    for (int i = 0; i < max_value; ++i) {
        auto value = queue.WaitAndPop();
        ASSERT_NE(value, nullptr);
    }
}

TEST(LockQueueTest, PushPopParallel) {
    queue::Locked<int> queue;
    const int max_value = 10000;

    std::thread t1(Push, std::ref(queue), max_value);
    Push(queue, max_value);
    t1.join();

    ASSERT_FALSE(queue.Empty());

    std::thread t2(Pop, std::ref(queue), max_value);
    Pop(queue, max_value);
    t2.join();

    ASSERT_TRUE(queue.Empty());
}

TEST(LockStackTest, PushPopSimultaneously) {
    queue::Locked<int> queue;
    const int max_value = 10000;

    std::thread t(Push, std::ref(queue), max_value);
    Pop(queue, max_value);
    t.join();

    ASSERT_TRUE(queue.Empty());
}

} // namespace utils
} // namespace concurent
