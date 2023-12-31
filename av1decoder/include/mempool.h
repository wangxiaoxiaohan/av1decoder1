#include <vector>
#include <iostream>
class MemoryPool{
public:
    MemoryPool(size_t blockSize, size_t totalBlocks);
    ~MemoryPool();
    void *allocate();
    void deallocate(void* block);
private:
    private:
    std::vector<uint8_t*> memoryBlocks; // 存储内存块的指针
    size_t blockSize; // 内存块大小
    size_t totalBlocks; // 总共的内存块数量
    size_t allocatedBlocks; // 已分配的内存块数量
};