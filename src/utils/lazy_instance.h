#ifndef _TC_UTILS_LAZY_INSTANCE_H_
#define _TC_UTILS_LAZY_INSTANCE_H_

#include <memory>
#include <mutex>

namespace concurrent {
namespace utils {

template<class T>
class LazyInstance {
public:
  LazyInstance() = default;
  ~LazyInstance() = default;

  T& Get() {
    std::call_once(flag_, &LazyInstance::Init, this);
    return *data_;
  }

  const T& Get() const {
    std::call_once(flag_, &LazyInstance::Init, this);
    return *data_;
  }

private:
  LazyInstance(const LazyInstance&) = delete;
  LazyInstance(LazyInstance&&) = delete;

  LazyInstance& operator=(const LazyInstance&) = delete;
  LazyInstance& operator=(LazyInstance&&) = delete;

  void Init() {
    data_.reset(new T);
  }

  std::unique_ptr<T> data_;
  std::once_flag flag_;
};

} // namespace utils
} // namespace concurent

#endif // _TC_UTILS_LAZY_INSTANCE_H_
