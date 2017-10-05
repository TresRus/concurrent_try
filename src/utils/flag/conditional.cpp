#include <chrono>
#include <thread>

#include "utils/flag/conditional.h"

namespace concurrent {
namespace utils {
namespace flag {

void Conditional::Wait() {
  std::unique_lock<std::mutex> lock(mutex_);
  conditional_.wait(lock, [this] { return flag_; });
}

void Conditional::Set(bool value) {
  std::lock_guard<std::mutex> lock(mutex_);
  flag_ = value;
  conditional_.notify_one();
}

} // namespace flag
} // namespace utils
} // namespace concurrent
