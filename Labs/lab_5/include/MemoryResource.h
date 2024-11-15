#ifndef FIXEDBLOCKMEMORYRESOURCE_H
#define FIXEDBLOCKMEMORYRESOURCE_H

#include <memory_resource>
#include <vector>
#include <cassert>

class FixedBlockMemoryResource : public std::pmr::memory_resource {
public:
    FixedBlockMemoryResource(size_t blockSize, size_t blockCount);

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    size_t blockSize;
    size_t blockCount;
    std::vector<char> memory;
    std::vector<void*> freeBlocks;
};

#endif // FIXEDBLOCKMEMORYRESOURCE_H
