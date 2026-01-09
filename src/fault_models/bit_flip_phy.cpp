#include "bit_flip_phy.h"
#include "memory.h"

BitFlipPhy::BitFlipPhy(const std::set<size_t> &faultyAddresses) : faultyAddresses(faultyAddresses) {};

void BitFlipPhy::write(Memory *mem, size_t addr, uint8_t value)
{
    mem->write(addr, value);    // Обычная запись
}

uint8_t BitFlipPhy::read(Memory *mem, size_t addr) const
{
    if (faultyAddresses.contains(addr))
        return !mem->read(addr);    // Чтение инверсии
    return mem->read(addr);
}
