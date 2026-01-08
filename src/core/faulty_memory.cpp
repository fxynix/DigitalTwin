#include "faulty_memory.h"
#include "fault_model.h"
#include "memory.h"

FaultyMemory::FaultyMemory(Memory *m, FaultModel *f) : mem(m), fault(f) {}

void FaultyMemory::write(size_t addr, uint8_t value) {
    fault->write(mem, addr, value);
}

uint8_t FaultyMemory::read(size_t addr) const {
    return fault->read(mem, addr);
}

size_t FaultyMemory::size() const {
    return mem->size();
}