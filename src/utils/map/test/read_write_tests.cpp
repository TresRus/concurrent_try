#include "utils/map/read_write.h"

#include "gtest/gtest.h"

namespace concurrent {
namespace utils {

TEST(RWMapTest, GetDefault) { 
  map::ReadWrite<int, int> map;
  auto r = map.Get(1);
  ASSERT_EQ(r, 0);
}

} // namespace utils
} // namespace concurent
