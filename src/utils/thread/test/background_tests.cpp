#include "utils/thread/background.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

TEST(BackgroundThreadTest, OneTaskRunAdd) { 
  thread::Background bg;

  bg.Run();
  auto future = bg.Post([] () { return; });

  future.wait();
}

TEST(BackgroundThreadTest, OneTaskAddRun) { 
  thread::Background bg;

  auto future = bg.Post([] { ; });
  bg.Run();

  future.wait();
}

} // namespace utils
} // namespace concurrent
