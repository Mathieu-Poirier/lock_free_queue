#include "BufferSize.hpp"

#include <stdexcept>

void BufferSize::validate(const std::size_t &value) {
  if (value == 0) {
    throw std::invalid_argument("BufferSize cannot be 0");
  }

  if (value > MAX_BUFFER_SIZE) {
    throw std::invalid_argument("BufferSize cannot exceed MAX_BUFFER_SIZE");
  }
}

BufferSize::BufferSize(const std::size_t &value) : value_(value) {
  validate(value);
}

std::size_t BufferSize::get() const noexcept { return value_; }

void BufferSize::set(const std::size_t &value) {
  validate(value);
  value_ = value;
}

void BufferSize::set(const BufferSize &value) {
  validate(value.get());
  value_ = value.get();
}