#ifndef STUCK_AT_ZERO
#define STUCK_AT_ZERO

#include <set>

#include "fault_model.h"

class StuckAtZero : public FaultModel {
public:
    StuckAtZero(const std::set<size_t> &faultyAddresses);

    void write(Memory *mem, size_t addr, uint8_t value) override;
    uint8_t read(Memory *mem, size_t addr) const override;

private:
    std::set<size_t> faultyAddresses;
};

#endif // STUCK_AT_ZERO