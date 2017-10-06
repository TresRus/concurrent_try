#include "utils/flag/conditional.h"
#include "utils/flag/flag.h"
#include "utils/flag/spin.h"

namespace concurrent {
namespace utils {

Flag* Flag::Create(Flag::Type type) {
  switch (type) {
    case Type::SPIN:
      return new flag::Spin();
    case Type::CONDITIONAL:
      return new flag::Conditional();
    default:
      return nullptr;
  }
}

} // namespace utils
} // namespace concurrent

