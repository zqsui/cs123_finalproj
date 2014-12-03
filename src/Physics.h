#ifndef PHYSICS_H
#define PHYSICS_H


#include "math.h"
#include "GL/glew.h"
#include "glm/glm/glm.hpp"

glm::vec3 newtonSecondLaw(float mass, glm::vec3 a)
{
    return mass * a;
}

glm::vec3 accelVel(glm::vec3 v, glm::vec3 a, float delta_t)
{
    return v + a * delta_t;
}

glm::vec3 computeDisplacement(glm::vec3 v1, glm::vec3 v2, glm::vec3 a, float t)
{
    glm::vec3 s;
    s = v1 * t + 1.0/2 * a * t * t;
}







#endif // PHYSICS_H
