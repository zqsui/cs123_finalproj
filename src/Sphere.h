#ifndef SPHERE_H
#define SPHERE_H

#include "GL/glew.h"

class Sphere
{
public:
    //Uninitialized Sphere
    Sphere();

    //Initialized Sphere
    Sphere(const GLuint vertexLocation, const GLuint normalLocation);

    virtual ~Sphere();

    // Initialize Sphere: generate VAO, vertex data, and buffer it on GPU
    void init(const GLuint vertexLocation, const GLuint normalLocation);

    void draw();

private:
    bool m_isInitialized;
    GLuint m_vaoID;
    GLuint m_vbo;
};

#endif // SPHERE_H
