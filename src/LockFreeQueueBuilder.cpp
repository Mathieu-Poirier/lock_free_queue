#include "LockFreeQueueBuilder.hpp"
#include "BufferSize.hpp"
#include "LockFreeQueue.hpp"

#include <cstddef>
#include <stdexcept>

struct LockFreeQueueBuilder {
  BufferSize size;
  const char *filePath;
  BufferSize filePathLength;
};

// @ These two are sort of the same the initialize thing would probably be better if we overload what parameters we can pass
void LockFreeQueueBuilderInitialize(
    LockFreeQueueBuilder *lockFreeQueueBuilder) {
  lockFreeQueueBuilder->size = BufferSize(std::size_t{1});
  lockFreeQueueBuilder->filePath = "";
  lockFreeQueueBuilder->filePathLength = BufferSize(std::size_t{1});
}

LockFreeQueueBuilder *CreateLockFreeQueueBuilder() {
  return new LockFreeQueueBuilder{BufferSize(std::size_t{1uz}), "",
                                  BufferSize(std::size_t{1uz})};
}

void DestroyLockFreeQueueBuilder(LockFreeQueueBuilder *&lockFreeQueueBuilder) {
  delete lockFreeQueueBuilder;
  lockFreeQueueBuilder = nullptr;
}

void BuildSize(LockFreeQueueBuilder *lockFreeQueueBuilder,
               const BufferSize size) {
  lockFreeQueueBuilder->size.set(size);
}

void BuildFilePath(LockFreeQueueBuilder *lockFreeQueueBuilder,
                   const char *filePath, const BufferSize filePathLength) {
  if (filePath == nullptr) {
    throw std::invalid_argument(
        "You cannot make a LockFreeQueueBuilder with filePath == nullptr");
  }

  if (filePath[filePathLength.get() - 1] != '\0') {
    throw std::invalid_argument("You cannot make a LockFreeQueueBuilder with "
                                "something that is not null terminated");
  }

  lockFreeQueueBuilder->filePath = filePath;
  lockFreeQueueBuilder->filePathLength.set(filePathLength);
}