#include "Quad.h"

#include "Shader.h"

Quad::Quad(Shader &shader)
{
   // Create geometry
   //const int numEnts = 2*4;
   float rad = 1.0f;

   glm::vec3 vert[2*4];
   vert[0] = glm::vec3( -rad, -rad, 0 );    vert[1] = glm::vec3( 0, 0, 1 );
   vert[2] = glm::vec3(  rad, -rad, 0 );    vert[3] = glm::vec3( 0, 0, 1 );
   vert[4] = glm::vec3( -rad,  rad, 0 );    vert[5] = glm::vec3( 0, 0, 1 );
   vert[6] = glm::vec3(  rad,  rad, 0 );    vert[7] = glm::vec3( 0, 0, 1 );


   const int numEnts = 8 * 4;
   GLfloat vertexData[] = {
       -rad, -rad, 0,
       0, 0, 1,
       0, 0,
       rad, -rad, 0,
       0, 0, 1,
       1, 0,
       -rad, rad, 0,
       0, 0, 1,
       0, 1,
       rad, rad, 0,
       1, 1
   };


   size_t stride = sizeof( GLfloat )*3 + sizeof( GLfloat )*3 + sizeof( GLfloat )*2;
   //size_t stride = sizeof( GLfloat )*3 + sizeof( GLfloat )*3;

   //Generate VAO
   glGenVertexArrays( 1, &m_vao );
   glBindVertexArray( m_vao );

   //Generate VBO
   glGenBuffers( 1, &m_vbo );
   glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
   //glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec3 ) * numEnts, &vert[ 0 ].x, GL_STATIC_DRAW );
   glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * numEnts, vertexData, GL_STATIC_DRAW );

   //Bind the attribute positions positions
   glEnableVertexAttribArray( shader.attrib( "in_Position"  ) );
   glVertexAttribPointer( shader.attrib( "in_Position" ), 3, GL_FLOAT,GL_FALSE, stride, 0 );
   glEnableVertexAttribArray( shader.attrib( "in_Normal" ) );
   glVertexAttribPointer( shader.attrib( "in_Normal" ) ,3 , GL_FLOAT,GL_FALSE, stride, (void*) (3*sizeof(GLfloat)) );
   glEnableVertexAttribArray( shader.attrib( "texCoord" ) );
   glVertexAttribPointer( shader.attrib( "texCoord" ) ,3 , GL_FLOAT,GL_FALSE, stride, (void*) (6*sizeof(GLfloat)) );

   //Unbind buffers
   glBindVertexArray( 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

Quad::~Quad()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void Quad::draw()
{
   glBindVertexArray(m_vao);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   glBindVertexArray(0);
}
