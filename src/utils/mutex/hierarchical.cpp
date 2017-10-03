#include "hierarchical.h"

#include <climits>

namespace concurrent {
namespace utils {
namespace mutex {

thread_local unsigned long Hierarchical::thread_value_(ULONG_MAX);

HierarchicalError::HierarchicalError()
  : std::logic_error("Hierarchical mutex violation") {
}

Hierarchical::Hierarchical(unsigned long value)
  : value_(value),
    previous_value_(0) {}

void Hierarchical::lock() {
  Check();
  mutex_.lock();
  Update();
}

void Hierarchical::unlock() {
  thread_value_ = previous_value_;
  mutex_.unlock();
}

bool Hierarchical::try_lock() {
  Check();
  if (!mutex_.try_lock())
    return false;

  Update();
  return true;
}

void Hierarchical::Check() {
  if (thread_value_ <= value_)
    throw HierarchicalError();
}

void Hierarchical::Update() {
  previous_value_ = thread_value_;
  thread_value_ = value_;
}

} // namespace mutex
} // namespace utils
} // namespace concurrent
