#ifndef _TC_UTILS_FLAG_H_
#define _TC_UTILS_FLAG_H_

#include <mutex>

namespace concurrent {
namespace utils {

class Flag {
public:
  enum class Type {
    SPIN,
    CONDITIONAL
  };

  virtual void Wait() = 0;
  virtual void Set(bool value) = 0;

  static Flag* Create(Type type);
};

} // namespace utils
} // namespace concurrent

#endif // _TC_UTILS_FLAG_H_
