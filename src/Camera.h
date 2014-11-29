#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm/glm.hpp"

/**
    A basic camera
*/
// "near" and "far" used to be pointer modifiers in 16-bit DOS, and
// apparently are still #defined in <windows.h>
// #undef-ing them allows the lab to compile in Windows. Hooray for Windows!
#undef near
#undef far
struct LabCamera {
    glm::vec3 eye, center, up;
    float fovy, near, far;
};

#endif // CAMERA_H
