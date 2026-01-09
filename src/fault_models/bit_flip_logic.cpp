#include "bit_flip_logic.h"
#include "memory.h"

BitFlipLogical::BitFlipLogical(const std::set<size_t> &faultyAddresses) : faultyAddresses(faultyAddresses) {};

void BitFlipLogical::write(Memory *mem, size_t addr, uint8_t value)
{
    if (faultyAddresses.contains(addr))
        mem->write(addr, !value);    // Инверсная запись
    else
        mem->write(addr, value);
}

uint8_t BitFlipLogical::read(Memory *mem, size_t addr) const
{
    return mem->read(addr); // Обычное чтение
}
