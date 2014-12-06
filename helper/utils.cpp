#include <math.h>
#include "utils.h"
#include "glm/glm/glm.hpp"
#include <iostream>


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

glm::vec3 point2PlaneIntersectionPoint(glm::vec3 point_pos, Plane plane, glm::vec3 normal)
{
    float dist = point2PlaneDist(point_pos, plane);
    return point_pos + dist * (-normal);
}


bool isPointInPlane(glm::vec3 point_pos, Plane plane)
{
    glm::vec3 plane_params = glm::vec3(plane.a, plane.b, plane.c);
    if(!EQ(glm::dot(point_pos, plane_params)+plane.d, 0))
    {
//        std::cout<<"not on plane"<<std::endl;
        return false;
    }
    else
    {
        glm::vec3 centroid = plane.centroid;
        float width = plane.width;
        float height = plane.height;
        glm::vec3 offset = point_pos - centroid;
        float width_projection = fabs(glm::dot(offset, plane.width_vec));
        float height_projection = fabs(glm::dot(offset, plane.height_vec));

//        printVec3(point_pos);
//        printVec3(plane.centroid);
//        printVec3(offset);
//        std::cout<<width<<" "<<height<<std::endl;
        if((width/2 - width_projection > EPSILON)&&(height/2 - height_projection > EPSILON))
        {
//            std::cout<<"on plane!"<<std::endl;
            return true;
        }
        else
        {
//            std::cout<<"on plane, but out of bounds"<<std::endl;
            return false;
        }
    }
}



void printVec3(glm::vec3 vec3)
{
    std::cout<<vec3.x<<" "<<vec3.y<<" "<<vec3.z<<std::endl;
}
