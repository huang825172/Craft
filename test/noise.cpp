#include "../src/thirdParty/PerlinNoise-2.1/PerlinNoise.hpp"

#include <gtest/gtest.h>

siv::PerlinNoise noise;

TEST(Noise, getTwice)
{
    EXPECT_EQ(
        noise.accumulatedOctaveNoise1D_0_1(1.234, 8),
        noise.accumulatedOctaveNoise1D_0_1(1.234, 8));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}