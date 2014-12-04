#include <math.h>
#include "utils.h"
#include "glm/glm/glm.hpp"
#include "SceneData.h"



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


float point2PlaneDist(glm::vec3 point_pos, Plane plane)
{
    return fabs(point_pos.x * plane.a + point_pos.y * plane.b + point_pos.z * plane.c + plane.d)/(sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c));
}


float point2PointDist(glm::vec3 p1, glm::vec3 p2)
{
    return glm::length(p1 - p2);
}
