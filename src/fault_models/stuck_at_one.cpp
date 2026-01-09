#include "stuck_at_one.h"
#include "memory.h"

StuckAtOne::StuckAtOne(const std::set<size_t> &faultyAddresses) : faultyAddresses(faultyAddresses) {};

void StuckAtOne::write(Memory *mem, size_t addr, uint8_t value)
{
    if (faultyAddresses.contains(addr))
        mem->write(addr, 1);
    else
        mem->write(addr, value);
}

uint8_t StuckAtOne::read(Memory *mem, size_t addr) const
{
    if (faultyAddresses.contains(addr))
        return 1;
    return mem->read(addr);
}
