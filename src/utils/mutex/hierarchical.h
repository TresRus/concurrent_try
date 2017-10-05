#ifndef _TC_UTILS_MUTEX_HIERARCHICAL_H_
#define _TC_UTILS_MUTEX_HIERARCHICAL_H_

#include <exception>
#include <mutex>

namespace concurrent {
namespace utils {
namespace mutex {

struct HierarchicalError: std::logic_error {
  HierarchicalError();
};

class Hierarchical {
public:
  explicit Hierarchical(unsigned long value);

  void lock();
  void unlock();
  bool try_lock();

private:
  void Check();
  void Update();

  std::mutex mutex_;
  const unsigned long value_;
  unsigned long previous_value_;
  static thread_local unsigned long thread_value_;
};

} // namespace mutex
} // namespace utils
} // namespace concurrent

#endif // _TC_UTILS_MUTEX_HIERARCHICAL_H_
