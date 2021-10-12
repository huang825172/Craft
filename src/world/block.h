#pragma once

class Block
{
public:
    enum Type
    {
        Air,
        Dirt,
        Grass,
        GrassBlock,
        Leaf,
        Water,
        Wood
    };
    Type type = Grass;
};

extern char *BlockName[];