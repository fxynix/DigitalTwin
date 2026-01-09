#ifndef MARCH_B_TEST_H
#define MARCH_B_TEST_H

#include "test_algorithm.h"

class MarchB : public TestAlgorithm
{
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;
};

#endif // MARCH_B_TEST_H
