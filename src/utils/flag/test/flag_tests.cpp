#include <memory>
#include <thread>

#include "utils/flag/conditional.h"
#include "utils/flag/flag.h"
#include "utils/flag/spin.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

template<class T>
class FlagTest : public testing::Test {
public:
  void SetUp() {
    flag_ = std::make_unique<T>();
  }

protected:
  std::unique_ptr<Flag> flag_;
};

TYPED_TEST_CASE_P(FlagTest);

void SetFlag(Flag* flag) {
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  flag->Set(true);
}

TYPED_TEST_P(FlagTest, WaitFlag) { 
  std::thread t(SetFlag, this->flag_.get());

  this->flag_->Wait();
  t.join();
}

REGISTER_TYPED_TEST_CASE_P(FlagTest, WaitFlag);

typedef testing::Types<flag::Spin, flag::Conditional> FlagTypes;
INSTANTIATE_TYPED_TEST_CASE_P(FlagTests, FlagTest, FlagTypes);

} // namespace utils
} // namespace concurrent
