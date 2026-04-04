#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"

#include <functional>

// @ Parse this from CLI
constexpr unsigned int MAX_QUEUE_SIZE = 1024;
constexpr unsigned int MAX_FILEPATH_LENGTH = 4096;

struct LockFreeQueueBuilder {
    std::size_t size;
    const char* filePath;
    size_t filePathLength;
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

void BuildFilePath(LockFreeQueueBuilder* lockFreeQueueBuilder, const char* filePath, const std::size_t filePathLength){
    // Probably make some guards on input too
    if(filePath == nullptr){
        throw std::invalid_argument("You cannot make a LockFreeQueueBuilder with filePath == nullptr");
    }
    if(filePathLength <= 0){
        throw std::invalid_argument("You cannot make a LockFreeQueueBuilder with filePathLength <= 0");
    }
    // Need to enforce extra things in an encapsulated function on the caller side to minimize misuse where buffer can be larger than size which truncates
    if(filePathLength > MAX_FILEPATH_LENGTH){
        throw std::invalid_argument("You cannot make a LockFreeQueueBuilder with filePathLength > MAX_FILEPATH_LENGTH");
    }
    // @ Length to index, this is UB though so might still pass even when the string isn't null terminated presumably
    if(filePath[filePathLength - 1] != '\0'){
        throw std::invalid_argument("You cannot make a LockFreeQueueBuilder with something that is not null terminated");
    }
    // 
    // Set
    lockFreeQueueBuilder->filePath = filePath;
    // Max we will read from the buffer
    lockFreeQueueBuilder->filePathLength = filePathLength;
}