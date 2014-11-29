#ifndef QUAD_H
#define QUAD_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include "glm/glm/glm.hpp"

class Shader;

class Quad
{
   public:
      Quad() {}
      Quad(Shader &shader);
      ~Quad();

      void draw();

   private:
      GLuint m_vao;
      GLuint m_vbo;

      glm::mat4 m_modelViewMatrix;
};

#endif // QUAD_H
