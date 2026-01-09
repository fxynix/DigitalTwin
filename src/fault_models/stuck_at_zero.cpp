#include "stuck_at_zero.h"
#include "memory.h"

StuckAtZero::StuckAtZero(const std::set<size_t> &faultyAddresses) : faultyAddresses(faultyAddresses) {}

void StuckAtZero::write(Memory *mem, size_t addr, uint8_t value)
{
    if (faultyAddresses.contains(addr))
        mem->write(addr, 0);
    else
        mem->write(addr, value);
}

uint8_t StuckAtZero::read(Memory *mem, size_t addr) const
{
    if (faultyAddresses.contains(addr))
        return 0;
    return mem->read(addr);
}
