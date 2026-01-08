#ifndef FAULT_MODEL_H
#define FAULT_MODEL_H

#include <cstddef>
#include <cstdint>

class Memory;

class FaultModel {
public:
    virtual void write(Memory *mem, size_t addr, uint8_t value) = 0;
    virtual uint8_t read(Memory *mem, size_t addr) const = 0;
    virtual ~FaultModel() = default;
};

#endif // FAULT_MODEL_H