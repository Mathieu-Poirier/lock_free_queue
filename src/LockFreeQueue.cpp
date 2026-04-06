#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"
#include "Message.hpp"

struct LockFreeQueue {
  Message *messageContainer;
  BufferSize messageContainerLength;

  // Compare and swap these
  Message *enqueueCell;
  Message *dequeueCell;
};

/*
sequence numbers are used to determine the state of the cell and what wrap cycle the producers and soncumers are on
*/