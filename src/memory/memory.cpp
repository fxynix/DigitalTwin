#include "memory.h"

Memory::Memory(size_t size) : mem(size, 0) {}

void Memory::write(size_t addr, uint8_t value)
{
    if (addr < 0 || addr >= mem.size()) return;
    mem[addr] = value & 1;
}

uint8_t Memory::read(size_t addr) const
{
    if (addr < 0 || addr >= mem.size()) return UINT8_MAX;
    return mem[addr];
}

size_t Memory::size() const
{
    return mem.size();
}
