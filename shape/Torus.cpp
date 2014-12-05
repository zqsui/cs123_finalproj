#include "shape/Torus.h"
#include "math.h"

Torus::Torus(int param1, int param2, int param3, const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
    : Shape(param1, param2, param3)
{
    m_param1 = param1;
    m_param2 = param2;
    m_param3 = param3;


    int n_per_slice = 2* m_param1 - 2;
    m_n_triangle = n_per_slice * m_param2;
    auto_compute_m_n(m_n_triangle);
    //m_radius = 0.5;
    init(vertexLocation, normalLocation, textureLocation);

}

Torus::~Torus()
{

}

void Torus::init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
{
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    // Initialize the vertex buffer object.

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


    m_n_vertexData = m_param2 * 2* m_param1 * 3 * 6;

    m_vertexData = new GLfloat[m_n_vertexData];

    int cur_ind = 0; //current index of the vertexData

    float theta = 2 * M_PI / m_param1;
    float phi = 2 * M_PI / m_param2;
    float r = m_param3/200.;
    float R = 0.5 - r;
    glm::vec3 coord(0.0);
    glm::vec3 norm(0.0);

    for(int i = 0; i < m_param1; i++)
    {
        for(int j = 0; j < m_param2; j++)
        {
            //two triangles in each side
            //first triangle
            coord[0] = (R + r * cos(phi * j)) * cos(theta * i);
            coord[1] = (R + r * cos(phi * j)) * sin(theta * i);
            coord[2] = r * sin(phi * j);
            norm = glm::normalize(coord);
            m_vertexData[cur_ind++] = coord[0];
            m_vertexData[cur_ind++] = coord[1];
            m_vertexData[cur_ind++] = coord[2];
            m_vertexData[cur_ind++] = norm[0];
            m_vertexData[cur_ind++] = norm[1];
            m_vertexData[cur_ind++] = norm[2];

            coord[0] = (R + r * cos(phi * j)) * cos(theta * (i+1));
            coord[1] = (R + r * cos(phi * j)) * sin(theta * (i+1));
            coord[2] = r * sin(phi * j);
            norm = glm::normalize(coord);
            m_vertexData[cur_ind++] = coord[0];
            m_vertexData[cur_ind++] = coord[1];
            m_vertexData[cur_ind++] = coord[2];
            m_vertexData[cur_ind++] = norm[0];
            m_vertexData[cur_ind++] = norm[1];
            m_vertexData[cur_ind++] = norm[2];

            coord[0] = (R + r * cos(phi * (j + 1))) * cos(theta * (i+1));
            coord[1] = (R + r * cos(phi * (j + 1))) * sin(theta * (i+1));
            coord[2] = r * sin(phi * (j + 1));
            norm = glm::normalize(coord);
            m_vertexData[cur_ind++] = coord[0];
            m_vertexData[cur_ind++] = coord[1];
            m_vertexData[cur_ind++] = coord[2];
            m_vertexData[cur_ind++] = norm[0];
            m_vertexData[cur_ind++] = norm[1];
            m_vertexData[cur_ind++] = norm[2];

            //second triangle
            coord[0] = (R + r * cos(phi * (j + 1))) * cos(theta * i);
            coord[1] = (R + r * cos(phi * (j + 1))) * sin(theta * i);
            coord[2] = r * sin(phi * (j + 1));
            norm = glm::normalize(coord);
            m_vertexData[cur_ind++] = coord[0];
            m_vertexData[cur_ind++] = coord[1];
            m_vertexData[cur_ind++] = coord[2];
            m_vertexData[cur_ind++] = norm[0];
            m_vertexData[cur_ind++] = norm[1];
            m_vertexData[cur_ind++] = norm[2];

            coord[0] = (R + r * cos(phi * j)) * cos(theta * i);
            coord[1] = (R + r * cos(phi * j)) * sin(theta * i);
            coord[2] = r * sin(phi * j);
            norm = glm::normalize(coord);
            m_vertexData[cur_ind++] = coord[0];
            m_vertexData[cur_ind++] = coord[1];
            m_vertexData[cur_ind++] = coord[2];
            m_vertexData[cur_ind++] = norm[0];
            m_vertexData[cur_ind++] = norm[1];
            m_vertexData[cur_ind++] = norm[2];

            coord[0] = (R + r * cos(phi * (j + 1))) * cos(theta * (i+1));
            coord[1] = (R + r * cos(phi * (j + 1))) * sin(theta * (i+1));
            coord[2] = r * sin(phi * (j + 1));
            norm = glm::normalize(coord);
            m_vertexData[cur_ind++] = coord[0];
            m_vertexData[cur_ind++] = coord[1];
            m_vertexData[cur_ind++] = coord[2];
            m_vertexData[cur_ind++] = norm[0];
            m_vertexData[cur_ind++] = norm[1];
            m_vertexData[cur_ind++] = norm[2];

        }
    }


    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    glBufferData(GL_ARRAY_BUFFER, m_n_vertexData * sizeof(GLfloat), m_vertexData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLocation);
    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(
       vertexLocation,
       3,                   // Num coordinates per position
       GL_FLOAT,            // Type
       GL_FALSE,            // Normalized
       sizeof(GLfloat) * 6, // Stride
       (void*) 0            // Array buffer offset
    );
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




glm::vec3 Torus::getSphereNorm(float theta, float phi)
{
    return glm::vec3(sin(phi)*cos(theta), cos(phi), sin(phi)*sin(theta));
}



glm::vec3 Torus::getSphereCoord(float theta, float phi)
{
    return glm::vec3(m_radius * sin(phi)*cos(theta), m_radius * cos(phi), m_radius * sin(phi)*sin(theta));
}



float Torus::getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir)
{
    float px = eye_pos.x;
    float py = eye_pos.y;
    float pz = eye_pos.z;
    float dx = ray_dir.x;
    float dy = ray_dir.y;
    float dz = ray_dir.z;


    float a, b, c, t1, t2;

    a = dx * dx + dy * dy + dz * dz;
    b = 2.0 * (px * dx + py * dy + pz * dz);
    c = px * px + py * py + pz * pz - m_radius * m_radius;

    float inside_sqrt = b * b - 4.0 * a * c;
    if(inside_sqrt < 0)
        return INFINITY;

    t1 = (-1.0 * b + sqrt(inside_sqrt))/(2.0 * a);
    t2 = (-1.0 * b - sqrt(inside_sqrt))/(2.0 * a);
    if(t1 < EPSILON)
        t1 = INFINITY;
    if(t2 < EPSILON)
        t2 = INFINITY;

    return glm::min(t1, t2);
}

glm::vec4 Torus::getShapeNormal(glm::vec4 intersect_point)
{
    glm::vec4 norm = glm::vec4(intersect_point.x, intersect_point.y,
                               intersect_point.z, 0.0);
    return glm::normalize(norm);

}




glm::vec2 Torus::getShapeUV(glm::vec4 intersect_point)
{
   glm::vec2 uv_coord;
   float x = intersect_point.x;
   float y = intersect_point.y;
   float z = intersect_point.z;

   float phi = glm::asin(1.0 * y/0.5);
   uv_coord.y = 0.5 - phi/M_PI;
   if(fabs(y - 0.5) < EPSILON)
       uv_coord.x = 0.5;
   else
   {
       float theta = glm::atan(z, x);
       if(theta < 0)
           uv_coord.x = -1.0 * theta/(2.0 * M_PI);
       else
           uv_coord.x = 1.0 - 1.0 * theta/(2.0 * M_PI);
   }
   return uv_coord;
}
