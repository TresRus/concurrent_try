#ifndef _TC_UTILS_MAP_READ_WRITE_H_
#define _TC_UTILS_MAP_READ_WRITE_H_


#include <map>
#include <shared_mutex>

namespace concurrent {
namespace utils {
namespace map {

template<class K, class V>
class ReadWrite {
public:
  V Get(const K& key) const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto it = data_.find(key);
    return (it == data_.end()) ? V() : it->second;
  }

  void Set(const K& key, const V& value) {
    std::lock_guard<std::shared_mutex> lock(mutex_);
    data_[key] = value;
  }

private:
  std::map<K, V> data_;
  mutable std::shared_mutex mutex_;
};

} // namespace stack
} // namespace utils
} // namespace concurent

#endif // _TC_UTILS_MAP_READ_WRITE_H_
