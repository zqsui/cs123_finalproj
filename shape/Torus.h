#ifndef TORUS_H
#define TORUS_H


#include "Shape.h"
#include "GL/glew.h"
#include "math.h"

class Torus : public Shape
{
public:
    Torus(int param1, int param2, int param3, const GLuint vertexLocation,
          const GLuint normalLocation, const GLuint textureLocation);
   virtual ~Torus();
   void init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation);
   //void draw();
   glm::vec3 getSphereNorm(float theta, float phi);
   glm::vec3 getSphereCoord(float theta, float phi);

   float getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir);
   glm::vec4 getShapeNormal(glm::vec4 intersect_point);
   glm::vec2 getShapeUV(glm::vec4 intersect_point);
};


#endif // TORUS_H
