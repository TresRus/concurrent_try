#include <chrono>
#include <thread>

#include "utils/flag/spin.h"

namespace concurrent {
namespace utils {
namespace flag {

void Spin::Wait() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (!flag_) {
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    lock.lock();
  }
}

void Spin::Set(bool value) {
  std::lock_guard<std::mutex> lock(mutex_);
  flag_ = value;
}

} // namespace flag
} // namespace utils
} // namespace concurrent
