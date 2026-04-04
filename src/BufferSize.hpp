#pragma once
#include <cstddef>

constexpr std::size_t MAX_BUFFER_SIZE = 4096;

class BufferSize {
private:
  std::size_t value_;

  static void validate(const std::size_t &value);

public:
  explicit BufferSize(const std::size_t &value);

  BufferSize(char) = delete;
  BufferSize(signed char) = delete;
  BufferSize(unsigned char) = delete;
  BufferSize(bool) = delete;

  BufferSize(int) = delete;
  BufferSize(long) = delete;
  BufferSize(long long) = delete;

  BufferSize(unsigned int) = delete;
  // BufferSize(unsigned long) = delete;
  BufferSize(unsigned long long) = delete;

  ~BufferSize() = default;

  [[nodiscard]] std::size_t get() const noexcept;

  void set(const std::size_t &value);
  void set(const BufferSize &value);

  void set(char) = delete;
  void set(signed char) = delete;
  void set(unsigned char) = delete;
  void set(bool) = delete;

  void set(int) = delete;
  void set(long) = delete;
  void set(long long) = delete;

  void set(unsigned int) = delete;
  // void set(unsigned long) = delete;
  void set(unsigned long long) = delete;
};
