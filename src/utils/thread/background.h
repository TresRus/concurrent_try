#ifndef _TC_UTILS_THREAD_BACKGROUND_H_
#define _TC_UTILS_THREAD_BACKGROUND_H_

#include <future>
#include <utility>

#include "utils/queue/locked.h"

namespace concurrent {
namespace utils {
namespace thread {

class Background {
public:
  Background() = default;
  ~Background() = default;

  Background(const Background&) = delete;
  Background& operator=(const Background&) = delete;

  Background(Background&&) = delete;
  Background& operator=(Background&&) = delete;

  void Run();

  template<class Func>
  std::future<void> Post(Func);

private:
  void Loop();

  queue::Locked<std::packaged_task<void()>> tasks_;
};

template<class Func>
std::future<void> Background::Post(Func func) {
  std::packaged_task<void()> task(func);
  auto res = task.get_future();
  tasks_.Push(std::move(task));
  return res;
}

} // namespace thread
} // namespace utils
} // namespace concurrent

#endif // _TC_UTILS_THREAD_BACKGROUND_H_
