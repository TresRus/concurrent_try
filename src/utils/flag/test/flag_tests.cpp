#include <memory>
#include <thread>

#include "utils/flag/flag.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

class FlagTest : public testing::TestWithParam<Flag::Type> {
public:
  void SetUp() {
    flag_.reset(Flag::Create(GetParam()));
  }

protected:
  std::unique_ptr<Flag> flag_;
};

void SetFlag(Flag* flag) {
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  flag->Set(true);
}

TEST_P(FlagTest, WaitFlag) { 
  std::thread t(SetFlag, flag_.get());

  flag_->Wait();
  t.join();
}

INSTANTIATE_TEST_CASE_P(FlagTests, FlagTest,
    testing::Values(Flag::Type::SPIN, Flag::Type::CONDITIONAL));

} // namespace utils
} // namespace concurrent
