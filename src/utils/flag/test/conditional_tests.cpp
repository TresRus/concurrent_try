#include <thread>

#include "utils/flag/conditional.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

void SetFlag(flag::Conditional& flag) {
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  flag.Set(true);
}

TEST(ConditionalFlagTest, WaitFlag) { 
  flag::Conditional flag;

  std::thread t(SetFlag, std::ref(flag));

  flag.Wait();
  t.join();
}

} // namespace utils
} // namespace concurrent
