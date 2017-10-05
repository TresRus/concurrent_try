#ifndef _TC_UTILS_FLAG_CONDITIONAL_H_
#define _TC_UTILS_FLAG_CONDITIONAL_H_

#include <mutex>
#include <condition_variable>

namespace concurrent {
namespace utils {
namespace flag {

class Conditional {
public:
  void Wait();
  void Set(bool value);

private:
  bool flag_ = false;
  std::mutex mutex_;
  std::condition_variable conditional_;
};

} // namespace flag
} // namespace utils
} // namespace concurrent

#endif // _TC_UTILS_FLAG_CONDITIONAL_H_
