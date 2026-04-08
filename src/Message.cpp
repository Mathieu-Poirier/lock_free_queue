#include "Message.hpp"

#include <atomic>
#include <stdexcept>

struct Message {
  std::atomic<unsigned int> sequenceNumber;
  std::atomic<unsigned int> value;
};

Message *CreateMessage() { return new Message{0u, 0u}; }

void DestroyMessage(Message *&message) {
  delete message;
  message = nullptr;
}

BufferSize GetMessageSize() {
  return BufferSize(std::size_t{sizeof(Message)});
}

unsigned int GetSequenceNumber(const Message *message) {
  if (message == nullptr) {
    throw std::invalid_argument("Message is nullptr when passed to GetSequenceNumber");
  }
  return message->sequenceNumber.load(std::memory_order_relaxed);
}

void SetSequenceNumber(Message *message, unsigned int sequenceNumber) {
  if (message == nullptr) {
    throw std::invalid_argument("Message is nullptr when passed to SetSequenceNumber");
  }
  message->sequenceNumber.store(sequenceNumber, std::memory_order_relaxed);
}

unsigned int GetValue(const Message *message) {
  if (message == nullptr) {
    throw std::invalid_argument("Message is nullptr when passed to GetValue");
  }
  return message->value.load(std::memory_order_relaxed);
}

void SetValue(Message *message, unsigned int value) {
  if (message == nullptr) {
    throw std::invalid_argument("Message is nullptr when passed to SetValue");
  }
  message->value.store(value, std::memory_order_relaxed);
}
