#ifndef BIT_FLIP_LOGIC_H
#define BIT_FLIP_LOGIC_H

#include <set>
#include "fault_model.h"

class Memory;

class BitFlipLogical : public FaultModel
{
public:
    BitFlipLogical(const std::set<size_t> &faultyAddresses);

    void write(Memory *mem, size_t addr, uint8_t value) override;
    uint8_t read(Memory *mem, size_t addr) const override;

private:
    std::set<size_t> faultyAddresses;
};
#endif // BIT_FLIP_LOGIC_H
