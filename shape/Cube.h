#ifndef CUBE_H
#define CUBE_H

#define EPSILON_CUBE 0.001

#include "Shape.h"
#include "GL/glew.h"
#include "math.h"

class Cube : public Shape
{
public:
    Cube(int param1, int param2, int param3, const GLuint vertexLocation,
         const GLuint normalLocation, const GLuint textureLocation);
    virtual ~Cube();
    void init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation);
    float getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir);
    glm::vec4 getShapeNormal(glm::vec4 intersect_point);
    glm::vec2 getShapeUV(glm::vec4 intersect_point);
};

#endif // CUBE_H


