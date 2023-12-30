#include "mempool.h"
MemoryPool::MemoryPool(size_t blockSize, size_t totalBlocks) :
 blockSize(blockSize), totalBlocks(totalBlocks), allocatedBlocks(0) {
    // 初始化内存池
    for (size_t i = 0; i < totalBlocks; ++i) {
        uint8_t* block = new uint8_t[blockSize];
        memoryBlocks.push_back(block);
    }
}

MemoryPool::~MemoryPool() {
    // 释放内存池中的所有内存块
    for (uint8_t* block : memoryBlocks) {
        delete[] block;
    }
}

void* MemoryPool::allocate() {
    // 分配内存块
    if (allocatedBlocks < totalBlocks) {
        void* allocatedBlock = memoryBlocks[allocatedBlocks];
        ++allocatedBlocks;
        return allocatedBlock;
    } else {
        std::cout << "Memory pool exhausted!" << std::endl;
        return nullptr;
    }
}

void MemoryPool::deallocate(void* block) {
    // 释放内存块
    if (allocatedBlocks > 0) {
        --allocatedBlocks;
        memoryBlocks[allocatedBlocks] = static_cast<uint8_t*>(block);
    } else {
        std::cout << "No memory blocks to deallocate!" << std::endl;
    }
}
    