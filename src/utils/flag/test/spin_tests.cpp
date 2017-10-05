#include <thread>

#include "utils/flag/spin.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

void SetFlag(flag::Spin& flag) {
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  flag.Set(true);
}

TEST(SpinFlagTest, WaitFlag) { 
  flag::Spin flag;

  std::thread t(SetFlag, std::ref(flag));

  flag.Wait();
  t.join();
}

} // namespace utils
} // namespace concurrent
