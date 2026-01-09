#ifndef MARCH_LR_TEST_H
#define MARCH_LR_TEST_H

#include "test_algorithm.h"

class MarchLR : public TestAlgorithm
{
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;
};

#endif // MARCH_LR_TEST_H
