#ifndef CYLINDER_H
#define CYLINDER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include "glm/glm/glm.hpp"

class Shader;

class Cylinder
{
public:
    Cylinder(Shader &shader);
    ~Cylinder();

    void draw();

 private:
    GLuint m_vao;
    GLuint m_vbo;

    glm::mat4 m_modelViewMatrix;
};

#endif // CYLINDER_H
