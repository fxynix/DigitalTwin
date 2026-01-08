#ifndef FAULTY_MEMORY_H
#define FAULTY_MEMORY_H

#include <cstddef>
#include <cstdint>

class Memory;
class FaultModel;

class FaultyMemory {
public:
    FaultyMemory(Memory *m, FaultModel *f);

    void write(size_t addr, uint8_t value);
    uint8_t read(size_t addr) const;
    size_t size() const;

private:
    Memory *mem;
    FaultModel *fault;
};


#endif // FAULTY_MEMORY_H