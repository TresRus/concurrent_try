#ifndef _TC_UTILS_QUEUE_LOCKED_H_
#define _TC_UTILS_QUEUE_LOCKED_H_

#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>

namespace concurrent {
namespace utils {
namespace queue {

template<class T>
class Locked {
public:
  Locked();
  Locked(const Locked&);

  Locked& operator=(const Locked&) = delete;

  void Push(T);

  std::unique_ptr<T> TryPop();
  std::unique_ptr<T> WaitAndPop();
  bool Empty() const;

private:
  std::queue<T> data_;
  mutable std::mutex mutex_;
  std::condition_variable cv_;
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
  cv_.notify_one();
}

template<class T>
std::unique_ptr<T> Locked<T>::TryPop() {
  std::lock_guard<std::mutex> lock(mutex_);

  if (data_.empty())
    return nullptr;
  std::unique_ptr<T> res(std::make_unique<T>(data_.front()));
  data_.pop();

  return res;
}

template<class T>
std::unique_ptr<T> Locked<T>::WaitAndPop() {
  std::unique_lock<std::mutex> lock(mutex_);

  cv_.wait(lock, [this] { return !data_.empty(); });
  std::unique_ptr<T> res(std::make_unique<T>(data_.front()));
  data_.pop();

  return res;
}


template<class T>
bool Locked<T>::Empty() const {
  std::lock_guard<std::mutex> lock(mutex_);

  return data_.empty();
}

} // namespace queue
} // namespace utils
} // namespace concurent

#endif // _TC_UTILS_QUEUE_LOCKED_H_
