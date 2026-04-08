#pragma once

#include "BufferSize.hpp"

struct Message;

Message *CreateMessage();
void DestroyMessage(Message *&message);

BufferSize GetMessageSize();

unsigned int GetSequenceNumber(const Message *message);
void SetSequenceNumber(Message *message, unsigned int sequenceNumber);

unsigned int GetValue(const Message *message);
void SetValue(Message *message, unsigned int value);
