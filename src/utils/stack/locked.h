#ifndef _TC_UTILS_STACK_LOCKED_H_
#define _TC_UTILS_STACK_LOCKED_H_

#include <mutex>
#include <memory>
#include <stack>

namespace concurrent {
namespace utils {
namespace stack {

template<class T>
class Locked {
public:
  Locked();
  Locked(const Locked&);

  Locked& operator=(const Locked&) = delete;

  void Push(T);
  std::unique_ptr<T> Pop();
  bool Empty() const;

private:
  std::stack<T> data_;
  mutable std::mutex mutex_;
};

template<class T>
Locked<T>::Locked() {}

template<class T>
Locked<T>::Locked(const Locked& other) {
  std::lock_guard<std::mutex> lock(mutex_);
  data_ = other.data_;
}

template<class T>
void Locked<T>::Push(T value) {
  std::lock_guard<std::mutex> lock(mutex_);
  data_.push(value);
}

template<class T>
std::unique_ptr<T> Locked<T>::Pop() {
  std::lock_guard<std::mutex> lock(mutex_);

  if (data_.empty())
    return nullptr;
  std::unique_ptr<T> res(std::make_unique<T>(data_.top()));
  data_.pop();

  return res;
}

template<class T>
bool Locked<T>::Empty() const {
  std::lock_guard<std::mutex> lock(mutex_);

  return data_.empty();
}

} // namespace stack
} // namespace utils
} // namespace concurent

#endif // _TC_UTILS_STACK_LOCKED_H_
