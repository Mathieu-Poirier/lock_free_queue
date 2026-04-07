#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"
#include "Message.hpp"

struct LockFreeQueue {
  Message *messageContainer;
  BufferSize messageContainerLength;

  const char *filePath;
  // Compare and swap these
  Message *enqueueCell;
  Message *dequeueCell;
};

/*
sequence numbers are used to determine the state of the cell and what wrap cycle
the producers and soncumers are on
*/

LockFreeQueue* CreateQueue(LockFreeQueueBuilder *builder) {
  // @ Add these to the builder class, so we don't ahve to build with nullptr
  return new LockFreeQueue{nullptr, GetSize(builder), GetFilePath(builder), nullptr, nullptr};
}