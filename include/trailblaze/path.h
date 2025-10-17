/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cassert>
#include <iostream>
#include <memory_resource>
#include <stdexcept>
#include <string>
#include <vector>

#include "trailblaze/array_of_struct_storage.h"
#include "trailblaze/backport/span.h"
#include "trailblaze/type_traits.h"

namespace trailblaze {

/** A path is a container that holds an ordered sequence of states.
 *  This implementation abstracts the state type so that any state can be used.
 *  Also, the way the states are stored is determined by an underlying container.
 */
template <typename TState, template <typename, typename> class Storage = array_of_struct_storage,
          typename Allocator = std::allocator<TState>>
class path {
public:
  using value_type = TState;
  using allocator_type = Allocator;

  explicit path(const Allocator& allocator = Allocator()) : storage_(allocator) {}

  [[__nodiscard__]] std::size_t size() const noexcept {
    return storage_.size();
  }

  [[__nodiscard__]] bool empty() const noexcept {
    return size() == 0;
  }

  [[__nodiscard__]] TState* data() noexcept {
    return storage_.data();
  }

  [[__nodiscard__]] const TState* data() const noexcept {
    return storage_.data();
  }

  [[__nodiscard__]] span<TState> states() noexcept {
    return {data(), size()};
  }

  [[__nodiscard__]] span<const TState> states() const noexcept {
    return {data(), size()};
  }

  void reserve(std::size_t n) {
    storage_.reserve(n);
  }

  void resize(std::size_t n) {
    storage_.resize(n);
  }

  void push_back(const TState& state) {
    storage_.push_back(state);
  }

  void clear() noexcept {
    storage_.Clear();
  }

  [[__nodiscard__]] TState& start() {
    assert(!empty());
    return *data();
  }

  [[__nodiscard__]] const TState& start() const {
    assert(!empty());
    return *data();
  }

  [[__nodiscard__]] TState& goal() {
    assert(!empty());
    return *(data() + (size() - 1));
  }

  [[__nodiscard__]] const TState& goal() const {
    assert(!empty());
    return *(data() + (size() - 1));
  }

  [[__nodiscard__]] TState& operator[](std::size_t index) {
    return storage_[index];
  }

  [[__nodiscard__]] const TState& operator[](std::size_t index) const {
    return storage_[index];
  }

  [[__nodiscard__]] TState& at(std::size_t index) {
    if (index >= size()) {
      std::string msg = "index " + std::to_string(index) + " is out of range. Path size is " +
                        std::to_string(size());
      throw std::out_of_range(msg);
    }
    return storage_[index];
  }

  [[__nodiscard__]] const TState& at(std::size_t index) const {
    if (index >= size()) {
      std::string msg = "index " + std::to_string(index) + " is out of range. Path size is " +
                        std::to_string(size());
      throw std::out_of_range(msg);
    }
    return storage_[index];
  }

private:
  /// The underlying data storage.
  Storage<TState, Allocator> storage_;
};

// Polymorphic memory resource (PMR) alias.
template <typename TState>
using pmr_path = path<TState, array_of_struct_storage, std::pmr::polymorphic_allocator<TState>>;

/** Puts each state in a path onto an output stream.
 *
 *  TODO
 *
 */
template <typename TState, template <typename, typename> class Storage = array_of_struct_storage,
          typename Allocator = std::allocator<TState>>
inline std::ostream& operator<<(std::ostream& out, const path<TState>& path) {
  static_assert(is_ostream_insertable_v<TState>,
                "Requires that State is stream-insertable (has operator<<(ostream&, "
                "const State&)).");

  for (const auto& state : path.states()) {
    out << state << '\n';
  }
  return out;
}

} // namespace trailblaze
