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
template <typename S, typename Allocator>
struct AoSStorage {
  using Container = std::vector<S, Allocator>;

  explicit AoSStorage(const Allocator& a = Allocator()) : data_(a) {}

  S* DataPtr() noexcept {
    return data_.data();
  }

  const S* DataPtr() const noexcept {
    return data_.data();
  }

  std::size_t Size() const noexcept {
    return data_.size();
  }

  void Reserve(std::size_t n) {
    data_.reserve(n);
  }

  void Resize(std::size_t n) {
    data_.resize(n);
  }

  void PushBack(const S& v) {
    data_.push_back(v);
  }

  void Clear() noexcept {
    data_.clear();
  }

  Container data_;
};

// Vector-like contiguous path container.
template <typename State,
          template <typename, typename> class Storage = AoSStorage,
          typename Allocator                          = std::allocator<State>>
class Path {
public:
  using value_type     = State;
  using allocator_type = Allocator;

  explicit Path(const Allocator& a = Allocator()) : storage_(a) {}

  std::size_t size() const noexcept {
    return storage_.Size();
  }

  bool empty() const noexcept {
    return size() == 0;
  }

  State* data() noexcept {
    return storage_.DataPtr();
  }

  const State* data() const noexcept {
    return storage_.DataPtr();
  }

  span<State> states() noexcept {
    return {data(), size()};
  }

  span<const State> states() const noexcept {
    return {data(), size()};
  }

  void reserve(std::size_t n) {
    storage_.Reserve(n);
  }

  void resize(std::size_t n) {
    storage_.Resize(n);
  }

  void push_back(const State& s) {
    storage_.PushBack(s);
  }

  void clear() noexcept {
    storage_.Clear();
  }

  State& start() {
    assert(!empty());
    return *data();
  }

  const State& start() const {
    assert(!empty());
    return *data();
  }

  State& goal() {
    assert(!empty());
    return *(data() + (size() - 1));
  }

  const State& goal() const {
    assert(!empty());
    return *(data() + (size() - 1));
  }

  State& operator[](std::size_t index) {
    return *(data() + index);
  }

  const State& operator[](std::size_t index) const {
    return *(data() + index);
  }

  State& at(std::size_t index) {
    if (pos >= size()) {
      std::string msg =
          "pos " + std::to_string(pos) + " is out of range. Path size is " + std::to_string(size());
      throw std::out_of_range(msg);
    }
    return *(data() + index);
  }

  const State& at(std::size_t index) const {
    if (pos >= size()) {
      std::string msg =
          "pos " + std::to_string(pos) + " is out of range. Path size is " + std::to_string(size());
      throw std::out_of_range(msg);
    }
    return *(data() + index);
  }

private:
  Storage<State, Allocator> storage_;
};

// PMR convenience alias.
template <typename S>
using PmrPath = Path<S, AoSStorage, std::pmr::polymorphic_allocator<S>>;

/** Puts each state in a path onto an output stream.
 *
 *  TODO
 *
 */
template <typename State,
          template <typename, typename> class Storage = AoSStorage,
          typename Allocator                          = std::allocator<State>>
inline std::ostream& operator<<(std::ostream& os, const Path<State>& path) {
  static_assert(is_ostream_insertable_v<State>,
                "Requires that State is stream-insertable (has operator<<(ostream&, "
                "const State&)).");

  for (const auto& state : path.states()) {
    os << state << '\n';
  }
  return os;
}

} // namespace trailblaze

#endif
