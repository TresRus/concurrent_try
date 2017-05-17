#ifndef _TC_CONTAINERTS_STACK_H_
#define _TC_CONTAINERTS_STACK_H_

#include <mutex>
#include <memory>
#include <stack>

namespace concurrent {
namespace containers {

template<class T>
class Stack {
public:
    Stack();
    Stack(const Stack&);

    Stack& operator=(const Stack&) = delete;

    void Push(T);
    std::unique_ptr<T> Pop();
    bool Empty() const;

private:
    std::stack<T> data_;
    mutable std::mutex mutex_;
};

template<class T>
Stack<T>::Stack() {}

template<class T>
Stack<T>::Stack(const Stack& other) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_ = other.data_;
}

template<class T>
void Stack<T>::Push(T value) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.push(value);
}

template<class T>
std::unique_ptr<T> Stack<T>::Pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (data_.empty())
        return nullptr;
    std::unique_ptr<T> res(std::make_unique<T>(data_.top()));
    data_.pop();
    return res;
}

template<class T>
bool Stack<T>::Empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.empty();
}

} // namespace containers
} // namespace concurent

#endif // _TC_CONTAINERTS_STACK_H_
