#ifndef MARCH_A_TEST_H
#define MARCH_A_TEST_H

#include "test_algorithm.h"

class MarchA : public TestAlgorithm
{
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;
};

#endif // MARCH_A_TEST_H
