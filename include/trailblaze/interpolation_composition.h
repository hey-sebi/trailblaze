/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

namespace trailblaze {

/** Composition of interpolation functions.
 *
 *  In case a state space is a composite, state interpolation will usually also be a
 *  composite. This structs composes multiple atomic interpolator pieces, where each piece
 *  provides:
 *
 *  @code
 *   static void apply(const S& a, const S& b, double ratio, S& out);
 *  @endcode
 */
template <typename... Pieces>
struct interpolation_composition {
  template <typename T>
  T operator()(const T& a, const T& b, double ratio) const {
    // copy target layout, then overwrite touched components
    T out = b;
    (Pieces::apply(a, b, ratio, out), ...);
    return out;
  }
};

} // namespace trailblaze
