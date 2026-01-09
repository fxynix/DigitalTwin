#ifndef MARCH_C_TEST_H
#define MARCH_C_TEST_H

#include "test_algorithm.h"

class MarchC : public TestAlgorithm
{
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;
};

#endif // MARCH_C_TEST_H
