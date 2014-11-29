#include "Shader.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

Shader::Shader() : m_screenHeight( 600 ), m_screenWidth( 800 )
{
}

Shader::~Shader()
{
   glDeleteProgram(m_programHandle);
}

GLuint Shader::attrib( const std::string attribName )
{
    return glGetAttribLocation( m_programHandle, attribName.c_str() );
}

bool Shader::compile(void)
{
   if(!m_vertexShaderHandle)
   {
      printf("Could not compile shader program: Missing vertex shader.\n");
      return false;
   }
   if(!m_fragmentShaderHandle)
   {
      printf("Could not compile shader program: Missing fragment shader.\n");
      return false;
   }

   //Link shaders
   m_programHandle = glCreateProgram();
   glAttachShader(m_programHandle,m_vertexShaderHandle);
   glAttachShader(m_programHandle,m_fragmentShaderHandle);
   glLinkProgram(m_programHandle);

   //Check for errors
   GLint link_status;
   glGetProgramiv(m_programHandle,GL_LINK_STATUS,&link_status);
   if(link_status==GL_FALSE)
   {
      printf("Error linking shader program\n");

      char logBuf[1024];
      int len;
      glGetProgramInfoLog(m_programHandle, sizeof(logBuf), &len, logBuf);
      printf("Error: %s\n",logBuf);
      return false;
   }

   return true;
}

std::string Shader::getFragmentPath()
{
   return m_fragmentPath;
}

std::string Shader::getVertexPath()
{
   return m_vertexPath;
}

void Shader::loadFileToString(const char* path, char** string)
{
   std::ifstream sFile(path, std::ios::in|std::ios::binary|std::ios::ate);
   if(!sFile.is_open())
   {
      printf("Error: Could not open file: %s\n",path);
      return;
   }

   std::streampos size = sFile.tellg();
   (*string) = (char*) malloc(sizeof(char)*(size+1));
   memset(*string,0,size);
   sFile.seekg (0, std::ios::beg);
   sFile.read (*string, size);
   sFile.close();
   (*string)[size]=0;
}

bool Shader::loadFragmentShader(std::string path)
{
   char* shader_string = 0;
   GLint status;

   m_fragmentPath = path;

   m_fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
   if(!m_fragmentShaderHandle)
   {
      printf("Error: Could not create fragment shader.\n");
      return false;
   }
   loadFileToString(path.c_str(),&shader_string);
   if( shader_string == 0 )
   {
       printf("Error: Could not load fragment shader.\n");
       return false;
   }
   const GLchar* codeArray[] = {shader_string};
   glShaderSource(m_fragmentShaderHandle,1,codeArray,NULL);
   glCompileShader(m_fragmentShaderHandle);
   glGetShaderiv(m_fragmentShaderHandle, GL_COMPILE_STATUS,&status);
   if(status==GL_FALSE)
   {
      printf("Error: Could not compile fragment shader.\n");
   }
   free(shader_string);
   return true;
}

bool Shader::loadVertexShader(std::string path)
{
   char* shader_string = 0;
   GLint status;

   m_vertexPath = path;

   m_vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
   if(!m_vertexShaderHandle)
   {
      printf("Error: Could not create vertex shader.\n");
      return false;
   }
   loadFileToString(path.c_str(),&shader_string);
   if( shader_string == 0 )
   {
       printf("Error: Could not load vertex shader.\n");
       return false;
   }
   const GLchar* codeArray[] = {shader_string};
   glShaderSource(m_vertexShaderHandle,1,codeArray,NULL);
   glCompileShader(m_vertexShaderHandle);
   glGetShaderiv(m_vertexShaderHandle, GL_COMPILE_STATUS,&status);
   if(status==GL_FALSE)
   {
      printf("Error: Could not compile vertex shader.\n");
   }
   free(shader_string);
   return true;
}

void Shader::setSize(int width, int height)
{
   m_screenWidth = width;
   m_screenHeight = height;
}

void Shader::setUniform(const std::string uniformName, UNIFORM_TYPE type, void *t)
{
    switch( type )
    {
        case FLOAT:
            glUniform1fv( uniformLocation( uniformName ), 1, (GLfloat*) t );
            break;
        case VEC3:
            glUniform3fv( uniformLocation( uniformName ), 1, (GLfloat*) t);
            break;
        case VEC4:
            glUniform4fv( uniformLocation( uniformName ), 1, (GLfloat*) t );
            break;
        case MAT3:
            glUniformMatrix3fv( uniformLocation( uniformName ), 1, GL_FALSE, (GLfloat*) t );
            break;
        case MAT4:
            glUniformMatrix4fv( uniformLocation( uniformName ), 1, GL_FALSE, (GLfloat*) t );
            break;
        default:
            break;
    }
}

GLuint Shader::uniformLocation( const std::string uniformName )
{
   return glGetUniformLocation( m_programHandle, uniformName.c_str() );
}

void Shader::use(void)
{
   glUseProgram(m_programHandle);
}
