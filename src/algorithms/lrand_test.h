#ifndef LRAND_TEST_H
#define LRAND_TEST_H

#include "test_algorithm.h"

class LRANDTest : public TestAlgorithm
{
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;

private:
    uint32_t lcgNext(uint32_t current, uint32_t a, uint32_t c, uint32_t m) const;
    uint8_t generateData(uint32_t address, uint32_t iteration) const;
};

#endif // LRAND_TEST_H
