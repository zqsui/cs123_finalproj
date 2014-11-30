/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include "utils.h"

CamtransCamera::CamtransCamera()
{
    // @TODO: [CAMTRANS] Fill this in...
    m_near = 1.0;
    m_far = 30.0;
    m_h_angle_radian = 0;
    setAspectRatio(1.0);
    setHeightAngle(60.0);

    const glm::vec4 eye = glm::vec4(2.0, 2.0, 2.0, 1.0);
    const glm::vec4 look = glm::vec4(-1.0, -1.0, -1.0, 0.0);
    const glm::vec4 up = glm::vec4(0.0, 1.0, 0.0, 0.0);
    orientLook(eye, look, up);
//    m_position = glm::vec4(2.0, 2.0, 2.0, 1.0);
//    m_look = glm::vec4(0.0, 0.0, -1.0, 0.0);
//    m_up = glm::vec4(0.0, 1.0, 0.0, 0.0);

//    float m_look_magnitude = sqrt(glm::dot(m_look, m_look));
//    m_w = -m_look/m_look_magnitude;
//    m_v = m_up - (glm::dot(m_up, m_w)) * m_w;
//    float m_v_magnitude = sqrt(glm::dot(m_v, m_v));
//    m_v = m_v/m_v_magnitude;
//    glm::vec3 m_u_3 = glm::cross(vec4tovec3(m_v), vec4tovec3(m_w));
//    m_u = vec3HomCoord(m_u_3, 0.0);

//    m_u.w = 0.0;
//    m_v.w = 0.0;
//    m_w.w = 0.0;
}

void CamtransCamera::setAspectRatio(float a)
{
    // @TODO: [CAMTRANS] Fill this in...

    m_aspect = a;
    setHeightAngle(radians2Degree(m_h_angle_radian));
}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...

    return get_M1() * get_M2();
//    return glm::mat4x4();
}

glm::mat4x4 CamtransCamera::getViewMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...

    return get_M3() * get_M4();
//    return glm::mat4x4();
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...

    return glm::mat4x4();
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const
{
    // @TODO: [CAMTRANS] Fill this in...

    return get_M1();
//    return glm::mat4x4();
}

glm::mat4x4 CamtransCamera::getFilm2WorldMatrix() const
{
    return get_M4_inv() * get_M3_inv() * get_M2_inv();
}


glm::vec4 CamtransCamera::getPosition() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return m_position;
//    return glm::vec4();
}

glm::vec4 CamtransCamera::getLook() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return m_look;
//    return glm::vec4();
}

glm::vec4 CamtransCamera::getUp() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return m_up;
//    return glm::vec4();
}

float CamtransCamera::getAspectRatio() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return m_aspect;
//    return 0;
}

float CamtransCamera::getHeightAngle() const
{
    // @TODO: [CAMTRANS] Fill this in...
    return radians2Degree(m_h_angle_radian);
//    return 0;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up)
{
    // @TODO: [CAMTRANS] Fill this in...
//    std::cout<< eye.x <<" "<<eye.y<<" "<<eye.z<<" "<<eye.w<<std::endl;
//    std::cout<< look.x <<" "<<look.y<<" "<<look.z<<" "<<look.w<<std::endl;
//    std::cout<< up.x <<" "<<up.y<<" "<<up.z<<" "<<up.w<<std::endl;


    m_position = eye;
    m_position.w = 1.0;
    m_look = look;
    m_look.w = 0;
    m_up = up;

    float m_look_magnitude = sqrt(glm::dot(m_look, m_look));
    m_w = -m_look/m_look_magnitude;
    m_v = m_up - (glm::dot(m_up, m_w)) * m_w;
    float m_v_magnitude = sqrt(glm::dot(m_v, m_v));
    m_v = m_v/m_v_magnitude;
    glm::vec3 m_u_3 = glm::cross(vec4tovec3(m_v), vec4tovec3(m_w));
    m_u = vec3HomCoord(m_u_3, 0.0);

    m_u.w = 0.0;
    m_v.w = 0.0;
    m_w.w = 0.0;

    m_look = -m_w;
    m_up = m_v;
}

void CamtransCamera::setHeightAngle(float h) // h is a degree
{
    // @TODO: [CAMTRANS] Fill this in...
    m_h_angle_radian = degree2Radians(h);
    m_tan_h_2 = glm::tan(m_h_angle_radian/2.0);
    float L = m_far * m_tan_h_2;
    m_tan_w_2 = 1.0 * L * m_aspect/m_far;
}

void CamtransCamera::translate(const glm::vec4 &v)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_position += v;

}

void CamtransCamera::rotateU(float degrees)
{
    // @TODO: [CAMTRANS] Fill this in...
    float radians = degree2Radians(degrees);
    glm::mat4x4 rotMat = getRotation(m_position, m_u, radians);

    m_v = rotMat * m_v;
    m_w = rotMat * m_w;
    m_up = m_v;
    m_look = -m_w;
}

void CamtransCamera::rotateV(float degrees)
{
    // @TODO: [CAMTRANS] Fill this in...
    float radians = degree2Radians(degrees);
    glm::mat4x4 rotMat = getRotation(m_position, m_v, radians);

    m_u = rotMat * m_u;
    m_w = rotMat * m_w;
    m_up = m_v;
    m_look = -m_w;
}

void CamtransCamera::rotateW(float degrees)
{
    // @TODO: [CAMTRANS] Fill this in...
    float radians = degree2Radians(degrees);
    glm::mat4x4 rotMat = getRotation(m_position, m_w, radians);

    m_v = rotMat * m_v;
    m_u = rotMat * m_u;
    m_up = m_v;
    m_look = -m_w;
}

void CamtransCamera::setClip(float nearPlane, float farPlane)
{
    // @TODO: [CAMTRANS] Fill this in...
    m_near = nearPlane;
    m_far = farPlane;
}

float CamtransCamera::radians2Degree(float angle_radian) const
{
    return 1.0 * angle_radian * 180.0/M_PI;
}

float CamtransCamera::degree2Radians(float angle_degree) const
{
    return 1.0 * angle_degree * M_PI/180.0;
}


glm::mat4x4 CamtransCamera::get_M1() const
{
    float c = -1.0 * m_near/m_far;
    glm::mat4x4 tmp =  glm::mat4x4(1, 0, 0, 0,
                                   0, 1, 0, 0,
                                   0, 0, -1.0/(1+c), 1.0*c/(1+c),
                                   0, 0, -1, 0);
    return glm::transpose(tmp);
}

glm::mat4x4 CamtransCamera::get_M2() const
{
    glm::mat4x4 tmp = glm::mat4x4(1.0/(m_far * m_tan_w_2), 0, 0, 0,
                                  0, 1.0/(m_far * m_tan_h_2), 0, 0,
                                  0, 0, 1.0/m_far, 0,
                                  0, 0, 0, 1);
    return glm::transpose(tmp);
}

glm::mat4x4 CamtransCamera::get_M3() const
{
    glm::mat4x4 tmp = glm::mat4x4(m_u.x, m_u.y, m_u.z, 0,
                                  m_v.x, m_v.y, m_v.z, 0,
                                  m_w.x, m_w.y, m_w.z, 0,
                                  0, 0, 0, 1);
    return glm::transpose(tmp);
}

glm::mat4x4 CamtransCamera::get_M4() const
{
    glm::mat4x4 tmp = glm::mat4x4(1.0, 0, 0, -m_position.x,
                                  0, 1.0, 0, -m_position.y,
                                  0, 0, 1.0, -m_position.z,
                                  0, 0, 0, 1.0);
    return glm::transpose(tmp);
}





glm::mat4x4 CamtransCamera::get_M2_inv() const
{
    glm::mat4x4 tmp = glm::mat4x4(1.0*(m_far * m_tan_w_2), 0, 0, 0,
                                  0, 1.0*(m_far * m_tan_h_2), 0, 0,
                                  0, 0, 1.0*m_far, 0,
                                  0, 0, 0, 1);
    return glm::transpose(tmp);
}

glm::mat4x4 CamtransCamera::get_M3_inv() const
{
    glm::mat4x4 tmp = glm::mat4x4(m_u.x, m_v.x, m_w.x, 0,
                                  m_u.y, m_v.y, m_w.y, 0,
                                  m_u.z, m_v.z, m_w.z, 0,
                                  0, 0, 0, 1);
    return glm::transpose(tmp);
}

glm::mat4x4 CamtransCamera::get_M4_inv() const
{
    glm::mat4x4 tmp = glm::mat4x4(1.0, 0, 0, m_position.x,
                                  0, 1.0, 0, m_position.y,
                                  0, 0, 1.0, m_position.z,
                                  0, 0, 0, 1.0);
    return glm::transpose(tmp);
}
















glm::mat4x4 CamtransCamera::getRotation(glm::vec4 r_point, glm::vec4 r_axis, float r_radian)
{
    float y_radian = glm::atan(r_axis.z, r_axis.x);
    float xy_part = sqrt(r_axis.x * r_axis.x + r_axis.z * r_axis.z);
    float z_radian = -1.0 * glm::atan(r_axis.y, xy_part);

    glm::mat4x4 trans_ori = getTrans(-r_point);
    glm::mat4x4 trans_back = getTrans(r_point);
    glm::mat4x4 rot_y = getRotY(-y_radian);
    glm::mat4x4 rot_z = getRotZ(z_radian);
    glm::mat4x4 rot_x = getRotX(r_radian);
    glm::mat4x4 rot_y_back = getRotY(y_radian);
    glm::mat4x4 rot_z_back = getRotZ(-z_radian);

    return trans_back * rot_y_back * rot_z_back * rot_x * rot_z * rot_y * trans_ori;
}

glm::mat4x4 CamtransCamera::getRotX(float r_radian)
{
    float sin_r = glm::sin(r_radian);
    float cos_r = glm::cos(r_radian);
    glm::mat4x4 tmp = glm::mat4x4(1.0, 0, 0, 0,
                                  0, cos_r, -sin_r, 0,
                                  0, sin_r, cos_r, 0,
                                  0, 0, 0, 1.0);
    return glm::transpose(tmp);
}
glm::mat4x4 CamtransCamera::getRotY(float r_radian)
{
    float sin_r = glm::sin(r_radian);
    float cos_r = glm::cos(r_radian);
    glm::mat4x4 tmp = glm::mat4x4(cos_r, 0, -sin_r, 0,
                                  0, 1.0, 0, 0,
                                  sin_r, 0, cos_r, 0,
                                  0, 0, 0, 1.0);
    return glm::transpose(tmp);
}
glm::mat4x4 CamtransCamera::getRotZ(float r_radian)
{
    float sin_r = glm::sin(r_radian);
    float cos_r = glm::cos(r_radian);
    glm::mat4x4 tmp = glm::mat4x4(cos_r, -sin_r, 0, 0,
                                  sin_r, cos_r, 0, 0,
                                  0, 0, 1.0, 0,
                                  0, 0, 0, 1.0);
    return glm::transpose(tmp);
}

glm::mat4x4 CamtransCamera::getTrans(glm::vec4 trans_vec)
{
    glm::mat4x4 tmp = glm::mat4x4(1.0, 0, 0, trans_vec.x,
                                  0, 1.0, 0, trans_vec.y,
                                  0, 0, 1.0, trans_vec.z,
                                  0, 0, 0, 1.0);
    return glm::transpose(tmp);
}

glm::mat4x4 CamtransCamera::getScale(glm::vec4 scale_vec)
{
    glm::mat4x4 tmp = glm::mat4x4(scale_vec.x, 0, 0, 0,
                                  0, scale_vec.y, 0, 0,
                                  0, 0, scale_vec.z, 0,
                                  0, 0, 0, 1.0);
    return glm::transpose(tmp);
}
