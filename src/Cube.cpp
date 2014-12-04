#include "Cube.h"
#include <math.h>
#include <algorithm>


Cube::Cube(int param1, int param2, int param3, const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
    :Shape(param1, param2, param3)
{
    m_param1 = param1;
    m_param2 = param2;
    m_param3 = param3;
    int n_per_side = m_param1 * m_param1 * 2;
    m_n_triangle = n_per_side * 6;
    auto_compute_m_n(m_n_triangle);

    init(vertexLocation, normalLocation, textureLocation);
}

Cube::~Cube()
{
//    glDeleteBuffers(1, &m_vboID);
//    glDeleteVertexArrays(1, &m_vaoID);
//    delete [] m_vertexData;
//    m_vertexData = 0;
}


void Cube::init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
{

    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    // Initialize the vertex buffer object.

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


    m_vertexData = new GLfloat[m_n_vertexData];


    glm::vec3 norm_face;


    glm::vec3 lower_right;
    glm::vec3 lower_left;
    glm::vec3 top_right;
    glm::vec3 top_left;


    int i, j, index;
    float side_tri = 2 * m_radius / m_param1;
    float cur_x, cur_y, cur_z, next_x, next_y, next_z;
    float const_coord;

    index = 0;
    // front
    const_coord = 0.5;
    norm_face = glm::vec3(0, 0, 1);
    for(i = 0; i < m_param1; i++)
    {
        cur_x = -m_radius + side_tri * i;
        next_x = cur_x + side_tri;
        for(j = 0; j < m_param1; j++)
        {
            cur_y = -m_radius + side_tri * j;
            next_y = cur_y + side_tri;

            top_right = glm::vec3(next_x, next_y, const_coord);
            top_left = glm::vec3(cur_x, next_y, const_coord);
            lower_left = glm::vec3(cur_x, cur_y, const_coord);
            lower_right = glm::vec3(next_x, cur_y, const_coord);

            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_face, norm_face, norm_face, norm_face);

            index += 36;

        }
    }

    // back
    const_coord = -0.5;
    norm_face = glm::vec3(0, 0, -1);
    for(i = 0; i < m_param1; i++)
    {
        cur_x = m_radius - side_tri * i;
        next_x = cur_x - side_tri;
        for(j = 0; j < m_param1; j++)
        {
            cur_y = -m_radius + side_tri * j;
            next_y = cur_y + side_tri;

            top_right = glm::vec3(next_x, next_y, const_coord);
            top_left = glm::vec3(cur_x, next_y, const_coord);
            lower_left = glm::vec3(cur_x, cur_y, const_coord);
            lower_right = glm::vec3(next_x, cur_y, const_coord);

            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_face, norm_face, norm_face, norm_face);

            index += 36;

        }
    }


    // top
    const_coord = 0.5;
    norm_face = glm::vec3(0, 1, 0);
    for(i = 0; i < m_param1; i++)
    {
        cur_x = -m_radius + side_tri * i;
        next_x = cur_x + side_tri;
        for(j = 0; j < m_param1; j++)
        {
            cur_z = m_radius - side_tri * j;
            next_z = cur_z - side_tri;

            top_right = glm::vec3(next_x, const_coord, next_z);
            top_left = glm::vec3(cur_x, const_coord, next_z);
            lower_left = glm::vec3(cur_x, const_coord, cur_z);
            lower_right = glm::vec3(next_x, const_coord, cur_z);

            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_face, norm_face, norm_face, norm_face);

            index += 36;

        }
    }

    // bottom
    const_coord = -0.5;
    norm_face = glm::vec3(0, -1, 0);
    for(i = 0; i < m_param1; i++)
    {
        cur_x = -m_radius + side_tri * i;
        next_x = cur_x + side_tri;
        for(j = 0; j < m_param1; j++)
        {
            cur_z = -m_radius + side_tri * j;
            next_z = cur_z + side_tri;

            top_right = glm::vec3(next_x, const_coord, next_z);
            top_left = glm::vec3(cur_x, const_coord, next_z);
            lower_left = glm::vec3(cur_x, const_coord, cur_z);
            lower_right = glm::vec3(next_x, const_coord, cur_z);

            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_face, norm_face, norm_face, norm_face);

            index += 36;

        }
    }


    // right side
    const_coord = 0.5;
    norm_face = glm::vec3(1, 0, 0);
    for(i = 0; i < m_param1; i++)
    {
        cur_y = -m_radius + side_tri * i;
        next_y = cur_y + side_tri;
        for(j = 0; j < m_param1; j++)
        {
            cur_z = -m_radius + side_tri * j;
            next_z = cur_z + side_tri;

            top_right = glm::vec3(const_coord, next_y , next_z);
            top_left = glm::vec3(const_coord, cur_y,  next_z);
            lower_left = glm::vec3(const_coord, cur_y , cur_z);
            lower_right = glm::vec3(const_coord, next_y, cur_z);

            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_face, norm_face, norm_face, norm_face);

            index += 36;

        }
    }

    // left side
    const_coord = -0.5;
    norm_face = glm::vec3(-1, 0, 0);
    for(i = 0; i < m_param1; i++)
    {
        cur_y = m_radius - side_tri * i;
        next_y = cur_y - side_tri;
        for(j = 0; j < m_param1; j++)
        {
            cur_z = -m_radius + side_tri * j;
            next_z = cur_z + side_tri;

            top_right = glm::vec3(const_coord, next_y , next_z);
            top_left = glm::vec3(const_coord, cur_y,  next_z);
            lower_left = glm::vec3(const_coord, cur_y , cur_z);
            lower_right = glm::vec3(const_coord, next_y, cur_z);

            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_face, norm_face, norm_face, norm_face);

            index += 36;

        }
    }
    // Pass vertex data to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, m_n_vertexData * sizeof(GLfloat), m_vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(
        vertexLocation,
        3,                   // Num coordinates per position
        GL_FLOAT,            // Type
        GL_FALSE,            // Normalized
        sizeof(GLfloat) * 6, // Stride
        (void*) 0            // Array buffer offset
    );

    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(
        normalLocation,
        3,           // Num coordinates per normal
        GL_FLOAT,    // Type
        GL_TRUE,     // Normalized
        sizeof(GLfloat) * 6,           // Stride
        (void*) (sizeof(GLfloat) * 3)    // Array buffer offset
    );



    // Unbind buffers.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}



float Cube::getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir)
{
    float px = eye_pos.x;
    float py = eye_pos.y;
    float pz = eye_pos.z;
    float dx = ray_dir.x;
    float dy = ray_dir.y;
    float dz = ray_dir.z;

    float t = INFINITY;
    float cur_t;
    float x, y, z;

    // front
    cur_t = (0.5 - pz)/(1.0*dz);
    x = px + cur_t * dx;
    y = py + cur_t * dy;
    if((x - 0.5 > EPSILON_CUBE)||(x + 0.5 < EPSILON_CUBE)||(y - 0.5 > EPSILON_CUBE)||(y + 0.5 < EPSILON_CUBE)||(cur_t < EPSILON_CUBE))
        cur_t = INFINITY;
    t = glm::min(t, cur_t);

    // back
    cur_t = (-0.5 - pz)/(1.0*dz);
    x = px + cur_t * dx;
    y = py + cur_t * dy;
    if((x - 0.5 > EPSILON_CUBE)||(x + 0.5 < EPSILON_CUBE)||(y - 0.5 > EPSILON_CUBE)||(y + 0.5 < EPSILON_CUBE)||(cur_t < EPSILON_CUBE))
        cur_t = INFINITY;
    t = glm::min(t, cur_t);

    // left
    cur_t = (-0.5 - px)/(1.0*dx);
    z = pz + cur_t * dz;
    y = py + cur_t * dy;
    if((z - 0.5 > EPSILON_CUBE)||(z + 0.5 < EPSILON_CUBE)||(y - 0.5 > EPSILON_CUBE)||(y + 0.5 < EPSILON_CUBE)||(cur_t < EPSILON_CUBE))
        cur_t = INFINITY;
    t = glm::min(t, cur_t);

    // right
    cur_t = (0.5 - px)/(1.0*dx);
    z = pz + cur_t * dz;
    y = py + cur_t * dy;
    if((z - 0.5 > EPSILON_CUBE)||(z + 0.5 < EPSILON_CUBE)||(y - 0.5 > EPSILON_CUBE)||(y + 0.5 < EPSILON_CUBE)||(cur_t < EPSILON_CUBE))
        cur_t = INFINITY;
    t = glm::min(t, cur_t);

    // top
    cur_t = (0.5 - py)/(1.0*dy);
    z = pz + cur_t * dz;
    x = px + cur_t * dx;
    if((z - 0.5 > EPSILON_CUBE)||(z + 0.5 < EPSILON_CUBE)||(x - 0.5 > EPSILON_CUBE)||(x + 0.5 < EPSILON_CUBE)||(cur_t < EPSILON_CUBE))
        cur_t = INFINITY;
    t = glm::min(t, cur_t);

    // bottom
    cur_t = (-0.5 - py)/(1.0*dy);
    z = pz + cur_t * dz;
    x = px + cur_t * dx;
    if((z - 0.5 > EPSILON_CUBE)||(z + 0.5 < EPSILON_CUBE)||(x - 0.5 > EPSILON_CUBE)||(x + 0.5 < EPSILON_CUBE)||(cur_t < EPSILON_CUBE))
        cur_t = INFINITY;
    t = glm::min(t, cur_t);


    return t;
}

glm::vec4 Cube::getShapeNormal(glm::vec4 intersect_point)
{
    if(fabs(intersect_point.z - 0.5) < EPSILON_CUBE)
        return glm::vec4(0.0, 0.0, 1.0, 0.0);
    else if(fabs(intersect_point.z + 0.5) < EPSILON_CUBE)
        return glm::vec4(0.0, 0.0, - 1.0, 0.0);
    else if(fabs(intersect_point.y - 0.5) < EPSILON_CUBE)
        return glm::vec4(0.0, 1.0, 0.0, 0.0);
    else if(fabs(intersect_point.y + 0.5) < EPSILON_CUBE)
        return glm::vec4(0.0, -1.0, 0.0, 0.0);
    else if(fabs(intersect_point.x - 0.5) < EPSILON_CUBE)
        return glm::vec4(1.0, 0.0, 0.0, 0.0);
    else if(fabs(intersect_point.x + 0.5) < EPSILON_CUBE)
        return glm::vec4(-1.0, 0.0, 0.0, 0.0);
    else
        return glm::vec4(0.0);
}


glm::vec2 Cube::getShapeUV(glm::vec4 intersect_point)
{
   glm::vec2 uv_coord;
   float x = intersect_point.x;
   float y = intersect_point.y;
   float z = intersect_point.z;

   if(fabs(intersect_point.z - 0.5) < EPSILON_CUBE)
   {
       uv_coord.x = x + 0.5;
       uv_coord.y = -y + 0.5;
   }
   else if(fabs(intersect_point.z + 0.5) < EPSILON_CUBE)
   {
       uv_coord.x = -x + 0.5;
       uv_coord.y = -y + 0.5;
   }
   else if(fabs(intersect_point.y - 0.5) < EPSILON_CUBE)
   {
       uv_coord.x = x + 0.5;
       uv_coord.y = z + 0.5;
   }
   else if(fabs(intersect_point.y + 0.5) < EPSILON_CUBE)
   {
       uv_coord.x = x + 0.5;
       uv_coord.y = -z + 0.5;
   }
   else if(fabs(intersect_point.x - 0.5) < EPSILON_CUBE)
   {
       uv_coord.x = -z + 0.5;
       uv_coord.y = -y + 0.5;
   }
   else if(fabs(intersect_point.x + 0.5) < EPSILON_CUBE)
   {
       uv_coord.x = z + 0.5;
       uv_coord.y = -y + 0.5;
   }
   else
   {
       uv_coord.x = 0.0;
       uv_coord.y = 0.0;
   }
   return uv_coord;
}

