#include "Shape.h"
#include <iostream>

Shape::Shape(int param1, int param2, int param3)
{
    m_param2 = param2;
    m_param1 = param1;
    m_param3 = param3;
    m_radius = 0.5;
    m_vertexData = 0;
    m_vertexData = NULL;
}
Shape::~Shape()
{
    if(m_vertexData != NULL)
    {
        glDeleteBuffers(1, &m_vboID);
        glDeleteVertexArrays(1, &m_vaoID);
        delete []m_vertexData;
        m_vertexData = 0;
    }
    //std::cout<<"destructed"<<std::endl;
}

void Shape::init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
{

}

void Shape::draw()
{
    glBindVertexArray(m_vaoID);
    //glDrawArrays(GL_TRIANGLES, 0, m_n_vertexData /* Number of vertices to draw */);
    glDrawArrays(GL_TRIANGLES, 0, m_n_vertex);
    glBindVertexArray(0);
}


void Shape::insert2vertexData(int index, glm::vec3 vertexCoord)
{
    m_vertexData[index] = vertexCoord.x;
    m_vertexData[index+1] = vertexCoord.y;
    m_vertexData[index+2] = vertexCoord.z;
}

void Shape::insert2vertexData_tri(int index, glm::vec3 vertexCoord1, glm::vec3 vertexCoord2, glm::vec3 vertexCoord3)
{
    insert2vertexData(index, vertexCoord1);
    insert2vertexData(index + 8, vertexCoord2);
    insert2vertexData(index + 16, vertexCoord3);
}

void Shape::insert2vertexData_rec(int index, glm::vec3 top_right, glm::vec3 top_left,glm::vec3 lower_left,glm::vec3 lower_right)
{
    insert2vertexData_tri(index, top_right, top_left, lower_left);
    insert2vertexData_tri(index+24, lower_left, lower_right, top_right);

}


void Shape::insert2vertexData2(int index, glm::vec2 vertexCoord)
{
    m_vertexData[index] = vertexCoord.x;
    m_vertexData[index+1] = vertexCoord.y;
}

void Shape::insert2vertexData_tri2(int index, glm::vec2 vertexCoord1, glm::vec2 vertexCoord2, glm::vec2 vertexCoord3)
{
    insert2vertexData2(index, vertexCoord1);
    insert2vertexData2(index + 8, vertexCoord2);
    insert2vertexData2(index + 16, vertexCoord3);
}

void Shape::insert2vertexData_rec2(int index, glm::vec2 top_right, glm::vec2 top_left,glm::vec2 lower_left,glm::vec2 lower_right)
{
    insert2vertexData_tri2(index, top_right, top_left, lower_left);
    insert2vertexData_tri2(index+24, lower_left, lower_right, top_right);

}

