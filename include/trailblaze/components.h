#ifndef TRAILBLAZE_COMPONENTS_H_
#define TRAILBLAZE_COMPONENTS_H_

#include <cstdint>

namespace trailblaze {

// Bitmask for "actively used components" selectors.
enum class ComponentMask : std::uint32_t {
  kNone = 0,
  kXy = 1u << 0,
  kYaw = 1u << 1,
  kAll = 0xFFFF'FFFFu
};

constexpr ComponentMask operator|(ComponentMask a, ComponentMask b) {
  return static_cast<ComponentMask>(static_cast<std::uint32_t>(a) |
                                    static_cast<std::uint32_t>(b));
}
constexpr bool Has(ComponentMask m, ComponentMask bit) {
  return (static_cast<std::uint32_t>(m) & static_cast<std::uint32_t>(bit)) !=
         0u;
}

}  // namespace trailblaze

#endif  // TRAILBLAZE_COMPONENTS_H_
