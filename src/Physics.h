#ifndef PHYSICS_H
#define PHYSICS_H

#include "Basketball.h"
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

glm::vec3 computeDisplacement(glm::vec3 v1, glm::vec3 a, float t)
{
    glm::vec3 s;
//    float tmp = 0.5;
//    s = v1 * t + 0.5 * t * t * a;
    s.x = v1.x * t + 1.0/2 * a.x * t * t;
    s.y = v1.y * t + 1.0/2 * a.y * t * t;
    s.z = v1.z * t + 1.0/2 * a.z * t * t;
    return s;
}


void momentumTheory(float m1, glm::vec3 &v1, float m2, glm::vec3 &v2, glm::vec3 hit_dir_obj1)
{
    glm::vec3 norm_hit_dir_obj1 = glm::normalize(hit_dir_obj1);
    glm::vec3 v1Plus = norm_hit_dir_obj1 * glm::dot(v1, norm_hit_dir_obj1);
    glm::vec3 v2Plus = -norm_hit_dir_obj1 * glm::dot(v2, -norm_hit_dir_obj1);
    glm::vec3 v1Minus = v1 - v1Plus;
    glm::vec3 v2Minus = v2 - v2Plus;

    glm::vec3 v1Plus_prime = (v1Plus * (m1 - m2) + 2 * m2 * v2Plus)/(m1 + m2);
    glm::vec3 v2Plus_prime = (v2Plus * (m2 - m1) + 2 * m1 * v1Plus)/(m1 + m2);

    v1 = v1Plus_prime + v1Minus;
    v2 = v2Plus_prime + v2Minus;
}


void momentumTheory(float m1, glm::vec3 &v1, float m2, glm::vec3 &v2, glm::vec3 hit_dir_obj1, float scale)
{
    glm::vec3 norm_hit_dir_obj1 = glm::normalize(hit_dir_obj1);
    glm::vec3 v1Plus = norm_hit_dir_obj1 * glm::dot(v1, norm_hit_dir_obj1);
    glm::vec3 v2Plus = -norm_hit_dir_obj1 * glm::dot(v2, -norm_hit_dir_obj1);
    glm::vec3 v1Minus = v1 - v1Plus;
    glm::vec3 v2Minus = v2 - v2Plus;

    glm::vec3 v1Plus_prime = (v1Plus * (m1 - m2) + 2 * m2 * v2Plus)/(m1 + m2);
    glm::vec3 v2Plus_prime = (v2Plus * (m2 - m1) + 2 * m1 * v1Plus)/(m1 + m2);


    v1Plus_prime = v1Plus_prime * scale;
    v2Plus_prime = v2Plus_prime * scale;
    v1 = v1Plus_prime + v1Minus;
    v2 = v2Plus_prime + v2Minus;
}






#endif // PHYSICS_H
