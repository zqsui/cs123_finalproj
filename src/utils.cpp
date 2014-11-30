#include <math.h>
#include "utils.h"
#include "glm/glm/glm.hpp"

int sub2ind(int width, int row, int col)
{
    return row * width + col;
}

float dist(int x1, int y1, int x2, int y2)
{
    int x = x1 - x2;
    int y = y2 - y1;
    float dist = sqrt(x * x + y * y);
    return dist;
}

float boundUpDown(float val, float up, float down)
{
    if(val > up)
        val = up;

    if(val<down)
        val = down;

    return val;

}

glm::vec4 vec3HomCoord(glm::vec3 vec3, float w)
{
    return glm::vec4(1.0 * vec3.x, 1.0 * vec3.y, 1.0 * vec3.z, w);
}

glm::vec3 vec4tovec3(glm::vec4 vec4)
{
    return glm::vec3(vec4.x, vec4.y, vec4.z);
}
