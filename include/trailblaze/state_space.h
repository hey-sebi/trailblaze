/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_STATE_SPACE_H_
#define TRAILBLAZE_STATE_SPACE_H_

namespace trailblaze {

/** Primary state space template.
 *  Specialize per state type to set defaults.
 *
 * @tparam TState the state type belonging to the state space
 */
template <typename TState>
struct StateSpace
{
  // using Metric = ...;
  // using Interpolation = ...;
};

}  // namespace trailblaze

#endif
