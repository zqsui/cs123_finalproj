#ifndef UTILS_H
#define UTILS_H
#include "glm/glm/glm.hpp"
#include "scene/SceneData.h"
#define _EPSILON_ 1e-6
#define EPSILON _EPSILON_

#define EQ(a, b) (fabs((a) - (b)) < _EPSILON_)
#define NEQ(a, b) (fabs((a) - (b)) > _EPSILON_)


int sub2ind(int width, int row, int col);
float dist(int x1, int y1, int x2, int y2);
float boundUpDown(float val, float up, float down);

glm::vec4 vec3HomCoord(glm::vec3 vec3, float w);
glm::vec3 vec4tovec3(glm::vec4 vec4);
float point2PointDist(glm::vec3 p1, glm::vec3 p2);
float point2PlaneDist(glm::vec3 point_pos, Plane plane);

glm::vec3 point2PlaneIntersectionPoint(glm::vec3 point_pos, Plane plane, glm::vec3 normal);
bool isPointInPlane(glm::vec3 point_pos, Plane plane);
void printVec3(glm::vec3 vec3);

#endif // UTILS_H
