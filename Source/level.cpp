#include "level.h"

#include "air.h"

Level :: Level()
{
    for ( int x = 0 ; x < 30 ; x++ )
    {
        for ( int y = 0 ; y < 30 ; y++ )
        {
            for ( int z = 0 ; z < 30 ; z++ )
            {
                m_blocks.at(x).at(y).at(z).push_back( Air() );
            }
        }
    }
}

Block&
Level :: operator ()( const int x, const int y, const int z )
{
    if ( x > m_blocks.size() ) return Air();
    if ( y > m_blocks.at(y).size() ) return Air();
    if ( y > m_blocks.at(y).at(z).size() ) return Air();

    return


