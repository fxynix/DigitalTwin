#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <cstdint>

class Memory
{
public:
    explicit Memory(size_t size);

    void write(size_t addr, uint8_t value);
    uint8_t read(size_t addr) const;
    size_t size() const;

private:
    std::vector<uint8_t> mem;
};

#endif // MEMORY_H
