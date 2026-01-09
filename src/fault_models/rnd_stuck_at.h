#ifndef RND_STUCK_AT_H
#define RND_STUCK_AT_H

#include <set>
#include "fault_model.h"

class Memory;

class RndStuckAt : public FaultModel
{
public:
    RndStuckAt(const std::set<size_t> &faultyAddresses);

    void write(Memory *mem, size_t addr, uint8_t value) override;
    uint8_t read(Memory *mem, size_t addr) const override;
    uint8_t generate(size_t addr) const;

private:
    std::set<size_t> faultyAddresses;
};

#endif // RND_STUCK_AT_H
