#ifndef CYLINDER_H
#define CYLINDER_H


#include "shape/Shape.h"

class Cylinder : public Shape
{
public:
    Cylinder(int param1, int param2, int param3, const GLuint vertexLocation,
             const GLuint normalLocation, const GLuint textureLocation);
    virtual ~Cylinder();
    void init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation);
    glm::vec3 getCylinderNorm(float theta);
    float getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir);
    glm::vec4 getShapeNormal(glm::vec4 intersect_point);
    glm::vec2 getShapeUV(glm::vec4 intersect_point);
};

#endif // CYLINDER_H
