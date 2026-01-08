#ifndef STUCK_AT_ONE_H
#define STUCK_AT_ONE_H

#include <set>
#include "fault_model.h"

class Memory;

class StuckAtOne : public FaultModel {
public:
    StuckAtOne(const std::set<size_t> &faultyAddresses);

    void write(Memory *mem, size_t addr, uint8_t value) override;
    uint8_t read(Memory *mem, size_t addr) const override;

private:
    std::set<size_t> faultyAddresses;
};

#endif // STUCK_AT_ONE_H
