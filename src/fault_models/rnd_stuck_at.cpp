#include "rnd_stuck_at.h"
#include "memory.h"

RndStuckAt::RndStuckAt(const std::set<size_t> &faultyAddresses) : faultyAddresses(faultyAddresses) {};

void RndStuckAt::write(Memory *mem, size_t addr, uint8_t value)
{
    if (faultyAddresses.contains(addr))
        mem->write(addr, generate(addr));   // записать псевдослуйчное StuckAt значение
    else
        mem->write(addr, value);
}

uint8_t RndStuckAt::read(Memory *mem, size_t addr) const
{
    if (faultyAddresses.contains(addr))
        return generate(addr);  // вернуть псевдослуйчное StuckAt значение
    return mem->read(addr);
}

uint8_t RndStuckAt::generate(size_t addr) const
{
    uint32_t hash = static_cast<uint32_t>(addr);
    hash = (hash * 1103515245 + 12345) & 0x7FFFFFFF;

    return (hash & 0x01) ? 1 : 0;
}

