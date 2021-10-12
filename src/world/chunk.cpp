#include "chunk.h"

Chunk::Chunk()
{
    coord = {0, 0};
    blocks = std::vector<std::vector<std::shared_ptr<Block>>>(
        chunkSize, std::vector<std::shared_ptr<Block>>(chunkSize));
    for (auto x = 0; x < chunkSize; x++)
        for (auto y = 0; y < chunkSize; y++)
        {
            blocks[x][y] = std::make_shared<Block>();
        }
}

std::shared_ptr<Chunk> Chunk::initialize(Vec2i coord)
{
    auto newChunk = std::make_shared<Chunk>();
    newChunk->coord = coord;
    return newChunk;
}