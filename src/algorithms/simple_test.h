#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include "test_algorithm.h"

class SimpleTest : public TestAlgorithm {
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;
};

#endif // SIMPLE_TEST_H