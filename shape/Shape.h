#ifndef SHAPE_H
#define SHAPE_H
//#define EPSILON 0.0001
#include "GL/glew.h"
#include "glm/glm/glm.hpp"
#include "helper/utils.h"
class Shape
{
public:
    Shape(int param1, int param2, int param3);
    virtual ~Shape();
    virtual void init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation);
    virtual void draw();
    virtual GLfloat* getvertexData(){return m_vertexData;}
    int getVertexNumber(){return m_n_vertex;}
    int getTriangleNumber(){return m_n_triangle;}

    virtual void auto_compute_m_n(int n_triangle)
    {m_n_vertex = m_n_triangle * 3 * 3; m_n_vertexData = m_n_vertex * 2;}

    virtual void insert2vertexData(int index, glm::vec3 vertexCoord);
    virtual void insert2vertexData_tri(int index, glm::vec3 vertexCoord1, glm::vec3 vertexCoord2,glm::vec3 vertexCoord3);
    virtual void insert2vertexData_rec(int index, glm::vec3 top_right, glm::vec3 top_left,glm::vec3 bottom_left,glm::vec3 bottom_right);

    virtual void insert2vertexData2(int index, glm::vec2 vertexCoord);
    virtual void insert2vertexData_tri2(int index, glm::vec2 vertexCoord1, glm::vec2 vertexCoord2,glm::vec2 vertexCoord3);
    virtual void insert2vertexData_rec2(int index, glm::vec2 top_right, glm::vec2 top_left,glm::vec2 bottom_left,glm::vec2 bottom_right);

    virtual float getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir) = 0; //{return INFINITY;}
    virtual glm::vec4 getShapeNormal(glm::vec4 intersect_point) = 0; //{return glm::vec4(1.0, 0.0, 0.0, 0.0);}
    virtual glm::vec2 getShapeUV(glm::vec4 intersect_point) = 0;


protected:
    GLuint m_vaoID;
    GLuint m_vboID;
    int m_param1;
    int m_param2;
    int m_param3;
    GLfloat *m_vertexData;
    int m_n_triangle;
    int m_n_vertex;
    int m_n_vertexData;
    float m_radius;
};

#endif // SHAPE_H
