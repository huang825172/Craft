#pragma once

#include "block.h"
#include "../misc/coord.h"

#include <memory>
#include <vector>

constexpr unsigned char chunkSize = 64;

class Chunk
{
public:
    Vec2i coord;
    std::vector<std::vector<std::shared_ptr<Block>>> blocks;
    std::shared_ptr<Chunk> links[Direction::Size];

    Chunk();

    static std::shared_ptr<Chunk> initialize(Vec2i);
};