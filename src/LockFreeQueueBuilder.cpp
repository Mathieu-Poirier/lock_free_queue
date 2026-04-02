#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"

#include <functional>

// @ Parse this from CLI
constexpr unsigned int MAX_QUEUE_SIZE = 1024;

struct LockFreeQueueBuilder {
    std::size_t size;
};

void LockFreeQueueBuilderInitialize(LockFreeQueueBuilder* lockFreeQueueBuilder){
    lockFreeQueueBuilder->size = 0uz;
}

LockFreeQueueBuilder* CreateLockFreeQueueBuilder(){
    LockFreeQueueBuilder* builder = new LockFreeQueueBuilder{};
    LockFreeQueueBuilderInitialize(builder);
    return builder;
}

void DestroyLockFreeQueueBuilder(LockFreeQueueBuilder*& lockFreeQueueBuilder){
    delete lockFreeQueueBuilder;
    lockFreeQueueBuilder = nullptr;
}

void BuildSize(LockFreeQueueBuilder* lockFreeQueueBuilder, std::size_t size){
    if(size == 0uz){
        throw std::invalid_argument("You cannot make a LockFreeQueueBuilder with size equal to 0");
    }
    
    if(size > MAX_QUEUE_SIZE){
        throw std::invalid_argument("You cannot make a LockFreeQueueBuilder with size > MAX_QUEUE_SIZE");
    }
    lockFreeQueueBuilder->size = size;
}