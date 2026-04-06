#include <atomic>
#include <cstddef>
#include "Message.hpp"

struct Message{
  std::atomic<unsigned int> sequenceNumber;
  std::atomic<unsigned int> value;
};

/*

Get the value of the message

change the value

compare if the value is still the same as when the function started

swap values

*/