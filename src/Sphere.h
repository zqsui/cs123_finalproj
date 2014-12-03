//#ifndef SPHERE_H
//#define SPHERE_H

//#include "GL/glew.h"

//class Sphere
//{
//public:
//    //Uninitialized Sphere
//    Sphere();

//    //Initialized Sphere
//    Sphere(const GLuint vertexLocation, const GLuint normalLocation);

//    virtual ~Sphere();

//    // Initialize Sphere: generate VAO, vertex data, and buffer it on GPU
//    void init(const GLuint vertexLocation, const GLuint normalLocation);

//    void draw();

//private:
//    bool m_isInitialized;
//    GLuint m_vaoID;
//    GLuint m_vbo;
//};

//#endif // SPHERE_H





#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "GL/glew.h"
#include "math.h"
class Sphere : public Shape
{
public:
    Sphere(int param1, int param2, int param3, const GLuint vertexLocation,
           const GLuint normalLocation, const GLuint textureLocation);
    virtual ~Sphere();
    void init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation);
    //void draw();
    glm::vec3 getSphereNorm(float theta, float phi);
    glm::vec3 getSphereCoord(float theta, float phi);

    float getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir);
    glm::vec4 getShapeNormal(glm::vec4 intersect_point);
    glm::vec2 getShapeUV(glm::vec4 intersect_point);
//protected:
//    float m_radius;
};

#endif // SPHERE_H
