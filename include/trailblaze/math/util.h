/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

namespace trailblaze {
/** Calculates a squared value.
 *
 *  This is a utility function mostly to avoid clutter like having to write x * x and
 *  similar.
 *
 *  @param value The value to multiply with itself
 *  @returns the squared value.
 */
template <typename T>
inline T square(const T& value) {
  return value * value;
}

} // namespace trailblaze
