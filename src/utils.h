#ifndef UTILS_H
#define UTILS_H
#include "glm/glm/glm.hpp"

int sub2ind(int width, int row, int col);
float dist(int x1, int y1, int x2, int y2);
float boundUpDown(float val, float up, float down);

glm::vec4 vec3HomCoord(glm::vec3 vec3, float w);
glm::vec3 vec4tovec3(glm::vec4 vec4);



#endif // UTILS_H
