#include <thread>

#include "utils/thread/background.h"

namespace concurrent {
namespace utils {
namespace thread {

void Background::Run() {
  std::thread thread(&Background::Loop, this);
  thread.detach();
}

void Background::Loop() {
  while (true) {
    auto task = tasks_.WaitAndPop();
    (*task)();
  }
}

} // namespace thread
} // namespace utils
} // namespace concurrent

