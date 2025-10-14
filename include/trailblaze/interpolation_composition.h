/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_INTERPOLATION_COMPOSITION_H_
#define TRAILBLAZE_INTERPOLATION_COMPOSITION_H_

namespace trailblaze {

/** Composition of interpolation functions.
 *
 *  In case a state space is a composite, state interpolation will usually also be a
 *  composite. This structs composes multiple atomic interpolator pieces, where each piece
 *  provides:
 *
 *  @code
 *   void apply(const S& a, const S& b, double t, S& out) const;
 *  @endcode
 */
template <typename... Pieces>
struct interpolation_composition {
  template <typename T>
  T operator()(const T& a, const T& b, double t) const {
    // copy target layout, then overwrite touched components
    T out = b;
    (Pieces{}.apply(a, b, t, out), ...);
    return out;
  }
};

} // namespace trailblaze

#endif
