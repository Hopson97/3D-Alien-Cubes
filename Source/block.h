#ifndef BLOCK_H
#define BLOCK_H


class Block
{
    public:
        Block( const bool walkable );

        inline
        const bool
        isWalkable  () { return m_isWalkable; }

    private:
        bool m_isWalkable;
};

#endif // BLOCK_H
