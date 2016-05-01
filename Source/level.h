#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include <vector>

class Level
{
    public:
        Level();

        Block&
        operator ()( const int x, const int y, const int z );

    protected:

    private:
        std::vector<std::vector<std::vector<Block>>> m_blocks;
};

#endif // LEVEL_H
