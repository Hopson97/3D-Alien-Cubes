#include "vectors.h"

namespace vectors
{
    const std::vector<GLfloat> vertices =
    {
        0.0f, 0.0f,  1.0f,
        1.0f, 0.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  1.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
    };

    const std::vector<GLuint> indices =
    {
        0, 1, 2, 2, 3, 0,
        3, 2, 6, 6, 7, 3,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 5, 6, 6, 2, 1
    };

}
