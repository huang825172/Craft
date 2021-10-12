#pragma once

#include "chunk.h"

#include <memory>

class World
{
public:
    std::shared_ptr<Chunk> rootChunk;

    World();

    void Tick();
    std::shared_ptr<Block> getBlock(int, int);

private:
    std::shared_ptr<Chunk> cachedChunk;
};