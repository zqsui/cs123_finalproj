#include "Cylinder.h"

#include "math.h"

Cylinder::Cylinder(int param1, int param2, int param3, const GLuint vertexLocation,
                   const GLuint normalLocation, const GLuint textureLocation)
    : Shape(param1, param2, param3)
{
    m_param1 = param1;
    m_param2 = param2;
    m_param3 = param3;

    int n_per_slice = 2* m_param1 - 1;
    int n_top = m_param2 * n_per_slice;
    int n_side = 2 * m_param1;

    m_n_triangle = 2 * n_top + n_side * m_param2;

    auto_compute_m_n(m_n_triangle);
    m_n_vertexData += m_n_triangle * 3 * 2;

    init(vertexLocation, normalLocation, textureLocation);
    //m_radius = 0.5;
}

Cylinder::~Cylinder()
{
//    glDeleteBuffers(1, &m_vboID);
//    glDeleteVertexArrays(1, &m_vaoID);
//    delete []m_vertexData;
//    m_vertexData = 0;
}


void Cylinder::init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
{
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    // Initialize the vertex buffer object.

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


    m_vertexData = new GLfloat[m_n_vertexData];


    glm::vec3 vertexTop = glm::vec3(0.0, m_radius, 0.0);
    glm::vec3 vertexBottom = glm::vec3(0.0, -m_radius, 0.0);
    glm::vec3 norm_top = glm::vec3(0.0, 1, 0.0);
    glm::vec3 norm_bottom = glm::vec3(0.0, -1, 0.0);

    glm::vec3 lower_right;
    glm::vec3 lower_left;
    glm::vec3 top_right;
    glm::vec3 top_left;
    glm::vec3 cur_norm;
    glm::vec3 next_norm;

    glm::vec2 tex_top;
    glm::vec2 tex_bottom;
    glm::vec2 tex_lower_right;
    glm::vec2 tex_lower_left;
    glm::vec2 tex_top_right;
    glm::vec2 tex_top_left;


    float cur_theta, next_theta, theta_bottom;
    theta_bottom = 2.0 * M_PI / m_param2;

    float radius_bottom = 1.0 * m_radius / m_param1;
    float side_length = 2 * m_radius / m_param1;
    float cur_radius, next_radius;
    float cur_y, next_y;
    float const_coord;


    int i, j, index;

    index =  0;

    // bottom
    const_coord = -m_radius;
    for(i = 0; i < m_param2; i++)
    {
        cur_theta = i * theta_bottom;
        next_theta = (i + 1) * theta_bottom;
        lower_left = glm::vec3(radius_bottom * cos(cur_theta), const_coord, radius_bottom * sin(cur_theta));
        lower_right = glm::vec3(radius_bottom * cos(next_theta), const_coord, radius_bottom * sin(next_theta));

        tex_bottom = getShapeUV(glm::vec4(vertexBottom, 1.0f));
        tex_lower_left = getShapeUV(glm::vec4(lower_left, 1.0f));
        tex_lower_right = getShapeUV(glm::vec4(lower_right, 1.0f));


        insert2vertexData_tri(index, vertexBottom, lower_left, lower_right);
        insert2vertexData_tri(index + 3, norm_bottom, norm_bottom, norm_bottom);
        insert2vertexData_tri2(index + 6, tex_bottom, tex_lower_left, tex_lower_right);
        //index += 18;
        index += 24;

        for(j = 1; j< m_param1; j++)
        {
            cur_radius = j * radius_bottom;
            next_radius = (j + 1) * radius_bottom;

            top_right = glm::vec3(next_radius * cos(cur_theta), const_coord, next_radius * sin(cur_theta));
            top_left = glm::vec3(next_radius * cos(next_theta), const_coord, next_radius * sin(next_theta));
            lower_left = glm::vec3(cur_radius * cos(next_theta), const_coord, cur_radius * sin(next_theta));
            lower_right = glm::vec3(cur_radius * cos(cur_theta), const_coord, cur_radius * sin(cur_theta));

            tex_top_right = getShapeUV(glm::vec4(top_right, 1.0f));
            tex_top_left = getShapeUV(glm::vec4(top_left, 1.0f));
            tex_lower_left = getShapeUV(glm::vec4(lower_left, 1.0f));
            tex_lower_right = getShapeUV(glm::vec4(lower_right, 1.0f));


            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_bottom, norm_bottom, norm_bottom, norm_bottom);
            insert2vertexData_rec2(index + 6, tex_top_right, tex_top_left, tex_lower_left, tex_lower_right);
            //index += 36;
            index += 48;
        }
    }

    // top
    const_coord = m_radius;
    for(i = 0; i < m_param2; i++)
    {
        cur_theta = i * theta_bottom;
        next_theta = (i + 1) * theta_bottom;
        lower_right = glm::vec3(radius_bottom * cos(cur_theta), const_coord, radius_bottom * sin(cur_theta));
        lower_left = glm::vec3(radius_bottom * cos(next_theta), const_coord, radius_bottom * sin(next_theta));

        tex_top = getShapeUV(glm::vec4(vertexTop, 1.0f));
        tex_lower_left = getShapeUV(glm::vec4(lower_left, 1.0f));
        tex_lower_right = getShapeUV(glm::vec4(lower_right, 1.0f));


        insert2vertexData_tri(index, vertexTop, lower_left, lower_right);
        insert2vertexData_tri(index + 3, norm_top, norm_top, norm_top);
        insert2vertexData_tri2(index + 6, tex_top, tex_lower_left, tex_lower_right);
        //index += 18;
        index += 24;

        for(j = 1; j < m_param1; j++)
        {
            cur_radius = j * radius_bottom;
            next_radius = (j + 1) * radius_bottom;

            lower_right = glm::vec3(next_radius * cos(cur_theta), const_coord, next_radius * sin(cur_theta));
            lower_left = glm::vec3(next_radius * cos(next_theta), const_coord, next_radius * sin(next_theta));
            top_left = glm::vec3(cur_radius * cos(next_theta), const_coord, cur_radius * sin(next_theta));
            top_right = glm::vec3(cur_radius * cos(cur_theta), const_coord, cur_radius * sin(cur_theta));

            tex_top_right = getShapeUV(glm::vec4(top_right, 1.0f));
            tex_top_left = getShapeUV(glm::vec4(top_left, 1.0f));
            tex_lower_left = getShapeUV(glm::vec4(lower_left, 1.0f));
            tex_lower_right = getShapeUV(glm::vec4(lower_right, 1.0f));


            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, norm_top, norm_top, norm_top, norm_top);
            insert2vertexData_rec2(index+6, tex_top_right, tex_top_left, tex_lower_left, tex_lower_right);
            //index += 36;
            index += 48;
        }
    }


    // side
    for(i = 0; i < m_param2; i++)
    {
        cur_theta = i * theta_bottom;
        next_theta = (i + 1) * theta_bottom;
        cur_norm = getCylinderNorm(cur_theta);
        next_norm = getCylinderNorm(next_theta);

        for(j = 0; j < m_param1; j++)
        {
            cur_y = -m_radius + j * side_length;
            next_y = cur_y + side_length;

            top_right = glm::vec3(m_radius * cos(cur_theta), next_y, m_radius * sin(cur_theta));
            top_left = glm::vec3(m_radius * cos(next_theta), next_y, m_radius * sin(next_theta));
            lower_left = glm::vec3(m_radius * cos(next_theta), cur_y, m_radius * sin(next_theta));
            lower_right = glm::vec3(m_radius * cos(cur_theta), cur_y, m_radius * sin(cur_theta));

            tex_top_right = getShapeUV(glm::vec4(top_right, 1.0f));
            tex_top_left = getShapeUV(glm::vec4(top_left, 1.0f));
            tex_lower_left = getShapeUV(glm::vec4(lower_left, 1.0f));
            tex_lower_right = getShapeUV(glm::vec4(lower_right, 1.0f));

            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index + 3, cur_norm, next_norm, next_norm, cur_norm);
            insert2vertexData_rec2(index+6, tex_top_right, tex_top_left, tex_lower_left, tex_lower_right);

            //index += 36;
            index += 48;
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
        sizeof(GLfloat) * 8, // Stride
        (void*) 0            // Array buffer offset
    );

    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(
        normalLocation,
        3,           // Num coordinates per normal
        GL_FLOAT,    // Type
        GL_TRUE,     // Normalized
        sizeof(GLfloat) * 8,           // Stride
        (void*) (sizeof(GLfloat) * 3)    // Array buffer offset
    );

    glEnableVertexAttribArray(textureLocation);
    glVertexAttribPointer(
        textureLocation,
        2,           // Num coordinates per normal
        GL_FLOAT,    // Type
        GL_FALSE,
        sizeof(GLfloat) * 8,           // Stride
        (void*) (sizeof(GLfloat) * 6)    // Array buffer offset
    );


    // Unbind buffers.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


glm::vec3 Cylinder::getCylinderNorm(float theta)
{
    return glm::vec3(cos(theta), 0, sin(theta));
}


float Cylinder::getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir)
{
    float px = eye_pos.x;
    float py = eye_pos.y;
    float pz = eye_pos.z;
    float dx = ray_dir.x;
    float dy = ray_dir.y;
    float dz = ray_dir.z;

    // side
    float a, b, c;
    a = dx * dx + dz * dz;
    b = 2.0 * px * dx + 2.0 * pz * dz;
    c = px * px + pz * pz - 0.25;

    float inside_sqrt = b * b - 4.0 * a * c;
    if(inside_sqrt < 0)
        return INFINITY;
    float t1, t2;
    t1 = (-1.0 * b + sqrt(inside_sqrt))/(2.0 * a);
    float x, y, z;
    y = py + t1 * dy;
    if((y + 0.5 < EPSILON)||(y - 0.5 > EPSILON)||(t1 < EPSILON))
        t1 = INFINITY;

    t2 = (-1.0 * b - sqrt(inside_sqrt))/(2.0 * a);
    y = py + t2 * dy;
    if((y + 0.5 < EPSILON)||(y - 0.5 > EPSILON)||(t2 < EPSILON))
        t2 = INFINITY;

    float t_side = glm::min(t1, t2);

    // top cap
    t1 = (0.5 - py)/dy;
    x = px + t1 * dx;
    z = pz + t1 * dz;
    if((x * x + z * z - 0.25 > EPSILON)||(t1 < EPSILON))
        t1 = INFINITY;

    t2 = (-0.5 - py)/dy;
    x = px + t2 * dx;
    z = pz + t2 * dz;
    if((x * x + z * z - 0.25 > EPSILON)||(t2 < EPSILON))
        t2 = INFINITY;

    float t_cap = glm::min(t1, t2);
    return glm::min(t_side, t_cap);
}

glm::vec4 Cylinder::getShapeNormal(glm::vec4 intersect_point)
{
//    glm::vec4 norm = glm::vec4(intersect_point.x, 0.0, intersect_point.z, 0.0);
//    return glm::normalize(norm);
    if(fabs(intersect_point.y + 0.5)<0.0001)
        return glm::vec4(0.0, -1.0, 0.0, 0.0);
    else if(fabs(intersect_point.y - 0.5)<0.0001)
        return glm::vec4(0.0, 1.0, 0.0, 0.0);
    else
    {
        glm::vec4 norm = glm::vec4(intersect_point.x, 0.0, intersect_point.z, 0.0);
        return glm::normalize(norm);
    }
}




glm::vec2 Cylinder::getShapeUV(glm::vec4 intersect_point)
{
   glm::vec2 uv_coord;
   float x = intersect_point.x;
   float y = intersect_point.y;
   float z = intersect_point.z;

   if(fabs(intersect_point.y + 0.5)<0.0001)
   {
       uv_coord.x = x + 0.5;
       uv_coord.y = -z + 0.5;
   }
   else if(fabs(intersect_point.y - 0.5)<0.0001)
   {
       uv_coord.x = x + 0.5;
       uv_coord.y = z + 0.5;
   }
   else
   {
       uv_coord.y = -y + 0.5;
       float theta = glm::atan(z, x);
       if(theta < 0)
           uv_coord.x = -1.0 * theta/(2.0 * M_PI);
       else
           uv_coord.x = 1.0 - 1.0 * theta/(2.0 * M_PI);
   }

   return uv_coord;
}


