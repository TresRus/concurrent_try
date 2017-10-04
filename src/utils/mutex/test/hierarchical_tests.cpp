#include <memory>

#include "utils/mutex/hierarchical.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

TEST(HierarchicalMutexTest, OneGuard) { 
  mutex::Hierarchical mutex(100);

  ASSERT_NO_THROW(std::lock_guard<mutex::Hierarchical> lock(mutex));
}

TEST(HierarchicalMutexTest, TwoGuards) { 
  mutex::Hierarchical mutex_100(100);
  mutex::Hierarchical mutex_200(200);

  std::lock_guard<mutex::Hierarchical> lock_200(mutex_200);
  ASSERT_NO_THROW(std::lock_guard<mutex::Hierarchical> lock_100(mutex_100));
}

TEST(HierarchicalMutexTest, TwoGuardsInvert) { 
  mutex::Hierarchical mutex_100(100);
  mutex::Hierarchical mutex_200(200);

  std::lock_guard<mutex::Hierarchical> lock_100(mutex_100);
  ASSERT_THROW(std::lock_guard<mutex::Hierarchical> lock_200(mutex_200),
      mutex::HierarchicalError);
}

TEST(HierarchicalMutexTest, TwoGuardsSame) { 
  mutex::Hierarchical mutex1(200);
  mutex::Hierarchical mutex2(200);

  std::lock_guard<mutex::Hierarchical> lock1(mutex1);
  ASSERT_THROW(std::lock_guard<mutex::Hierarchical> lock2(mutex2),
      mutex::HierarchicalError);
}

} // namespace utils
} // namespace concurrent
