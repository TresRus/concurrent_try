#include "utils/lazy_instance.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

struct Regular {
  Regular() {
    ++count_;
  }

  ~Regular() {
    --count_;
  }

  static int count_;
};

int Regular::count_ = 0;

TEST(LazyInstanceTest, NotUsed) { 
  LazyInstance<Regular> r;

  ASSERT_EQ(Regular::count_, 0);
}

TEST(LazyInstanceTest, Used) { 
  LazyInstance<Regular> r;

  r.Get();

  ASSERT_EQ(Regular::count_, 1);
}

} // namespace utils
} // namespace concurrent
