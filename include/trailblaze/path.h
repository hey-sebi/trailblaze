/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_PATH_H_
#define TRAILBLAZE_PATH_H_

#include <cassert>
#include <iostream>
#include <memory_resource>
#include <stdexcept>
#include <string>
#include <vector>

#include "trailblaze/backport/span.h"
#include "trailblaze/type_traits.h"

namespace trailblaze {

// Default AoS storage (allocator-aware).
template <typename T, typename Allocator>
struct array_of_struct_storage {
  using container_type = std::vector<T, Allocator>;

  explicit array_of_struct_storage(const Allocator& allocator = Allocator()) : data_(allocator) {}

  T* data() noexcept {
    return data_.data();
  }

  const T* data() const noexcept {
    return data_.data();
  }

  std::size_t size() const noexcept {
    return data_.size();
  }

  void reserve(std::size_t n) {
    data_.reserve(n);
  }

  void resize(std::size_t n) {
    data_.resize(n);
  }

  void push_back(const T& v) {
    data_.push_back(v);
  }

  void clear() noexcept {
    data_.clear();
  }

  /// Where the data is stored
  container_type data_;
};

// Vector-like contiguous path container.
template <typename TState,
          template <typename, typename> class Storage = array_of_struct_storage,
          typename Allocator                          = std::allocator<TState>>
class path {
public:
  using value_type     = TState;
  using allocator_type = Allocator;

  explicit path(const Allocator& allocator = Allocator()) : storage_(allocator) {}

  std::size_t size() const noexcept {
    return storage_.size();
  }

  bool empty() const noexcept {
    return size() == 0;
  }

  TState* data() noexcept {
    return storage_.data();
  }

  const TState* data() const noexcept {
    return storage_.data();
  }

  span<TState> states() noexcept {
    return {data(), size()};
  }

  span<const TState> states() const noexcept {
    return {data(), size()};
  }

  void reserve(std::size_t n) {
    storage_.reserve(n);
  }

  void resize(std::size_t n) {
    storage_.resize(n);
  }

  void push_back(const TState& s) {
    storage_.push_back(s);
  }

  void clear() noexcept {
    storage_.Clear();
  }

  TState& start() {
    assert(!empty());
    return *data();
  }

  const TState& start() const {
    assert(!empty());
    return *data();
  }

  TState& goal() {
    assert(!empty());
    return *(data() + (size() - 1));
  }

  const TState& goal() const {
    assert(!empty());
    return *(data() + (size() - 1));
  }

  TState& operator[](std::size_t index) {
    return *(data() + index);
  }

  const TState& operator[](std::size_t index) const {
    return *(data() + index);
  }

  TState& at(std::size_t index) {
    if (index >= size()) {
      std::string msg = "index " + std::to_string(index) + " is out of range. Path size is " +
                        std::to_string(size());
      throw std::out_of_range(msg);
    }
    return *(data() + index);
  }

  const TState& at(std::size_t index) const {
    if (index >= size()) {
      std::string msg = "index " + std::to_string(index) + " is out of range. Path size is " +
                        std::to_string(size());
      throw std::out_of_range(msg);
    }
    return *(data() + index);
  }

private:
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
template <typename TState,
          template <typename, typename> class Storage = array_of_struct_storage,
          typename Allocator                          = std::allocator<TState>>
inline std::ostream& operator<<(std::ostream& os, const path<TState>& path) {
  static_assert(is_ostream_insertable_v<TState>,
                "Requires that State is stream-insertable (has operator<<(ostream&, "
                "const State&)).");

  for (const auto& state : path.states()) {
    os << state << '\n';
  }
  return os;
}

} // namespace trailblaze

#endif
