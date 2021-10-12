#include "../src/world/world.h"

#include <gtest/gtest.h>

std::unique_ptr<World> world;

class WorldEnv : public testing::Environment
{
public:
    virtual void SetUp()
    {
        world = std::make_unique<World>();
    }
    virtual void TearDown() {
        world.reset();
    }
};

TEST(GetBlock, getAtRoot)
{
    EXPECT_TRUE(world->getBlock(20, 20)->type == Block::Type::Air);
}

TEST(GetBlock, getAtEmpty)
{
    EXPECT_TRUE(world->getBlock(130, 80)->type == Block::Type::Air);
}

TEST(GetBlock, getAtNegative)
{
    EXPECT_TRUE(world->getBlock(-34, -34)->type == Block::Type::Air);
}

int main(int argc, char **argv)
{
    testing::AddGlobalTestEnvironment(new WorldEnv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}