#ifndef _TC_UTILS_FLAG_SPIN_H_
#define _TC_UTILS_FLAG_SPIN_H_

#include <mutex>

namespace concurrent {
namespace utils {
namespace flag {

class Spin {
public:
  void Wait();
  void Set(bool value);

private:
  bool flag_ = false;
  std::mutex mutex_;
};

} // namespace flag
} // namespace utils
} // namespace concurrent

#endif // _TC_UTILS_FLAG_SPIN_H_
