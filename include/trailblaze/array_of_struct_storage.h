/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

namespace trailblaze {

/** Stores objects in an continuous (array-like) memory block.
 *  @see https://en.wikipedia.org/wiki/AoS_and_SoA
 */
template <typename T, typename Allocator>
class array_of_struct_storage {
public:
  using container_type = std::vector<T, Allocator>;

  explicit array_of_struct_storage(const Allocator& allocator = Allocator()) : data_(allocator) {}

  [[__nodiscard__]] T* data() noexcept {
    return data_.data();
  }

  [[__nodiscard__]] const T* data() const noexcept {
    return data_.data();
  }

  [[__nodiscard__]] std::size_t size() const noexcept {
    return data_.size();
  }

  [[__nodiscard__]] T& operator[](std::size_t index) {
    return data_[index];
  }

  [[__nodiscard__]] const T& operator[](std::size_t index) const {
    return data_[index];
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

private:
  /// Where the data is stored
  container_type data_;
};

} // namespace trailblaze
