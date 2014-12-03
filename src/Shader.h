#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "glm/glm/glm.hpp"

#include <string>
#include <vector>
#include <QString>

class Shader
{
   public:
      enum UNIFORM_TYPE { INT, FLOAT, VEC3, VEC4, MAT3, MAT4 };

      Shader();
      ~Shader();

      GLuint attrib( std::string );
      bool compile();
      std::string getVertexPath();
      std::string getFragmentPath();
      bool loadVertexShader(std::string);
      bool loadFragmentShader(std::string);
      void setSize(int width, int height);
      void setUniform(const std::string uniformName, UNIFORM_TYPE type, void *t );
      GLuint uniformLocation( const std::string );
      void use();

      GLuint loadTexture(const QString &path);


   private:

      GLuint m_screenHeight;
      GLuint m_screenWidth;

      int m_fragmentShaderHandle;
      int m_vertexShaderHandle;
      int m_programHandle;

      std::string m_vertexPath;
      std::string m_fragmentPath;

      void loadFileToString(const char* path, char** string);

};

#endif // SHADER_H
