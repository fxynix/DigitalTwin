#ifndef CHECKERBOARD_TEST_H
#define CHECKERBOARD_TEST_H

#include "test_algorithm.h"

class CheckerboardTest : public TestAlgorithm
{
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;
};

#endif // CHECKERBOARD_TEST_H
