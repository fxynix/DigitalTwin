#ifndef MATS_PLUS_PLUS_TEST_H
#define MATS_PLUS_PLUS_TEST_H

#include "test_algorithm.h"

class MATSPlusPlus : public TestAlgorithm
{
public:
    const char* name() const override;
    int run(FaultyMemory *mem) override;
};

#endif // MATS_PLUS_PLUS_TEST_H
