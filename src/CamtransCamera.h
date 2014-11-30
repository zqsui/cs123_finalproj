#ifndef CAMTRANSCAMERA_H
#define CAMTRANSCAMERA_H

#include "glm/glm/glm.hpp"


/**
 * @class CamtransCamera
 *
 * The perspective camera to be implemented in the Camtrans lab.
 */
class CamtransCamera
{
public:
    // Initialize your camera.
    CamtransCamera();

    // Sets the aspect ratio of this camera. Automatically called by the GUI when the window is
    // resized.
    virtual void setAspectRatio(float aspectRatio);

    // Returns the projection matrix given the current camera settings.
    virtual glm::mat4x4 getProjectionMatrix() const;

    // Returns the view matrix given the current camera settings.
    virtual glm::mat4x4 getViewMatrix() const;

    // Returns the matrix that scales down the perspective view volume into the canonical
    // perspective view volume, given the current camera settings.
    virtual glm::mat4x4 getScaleMatrix() const;

    // Returns the matrix the unhinges the perspective view volume, given the current camera
    // settings.
    virtual glm::mat4x4 getPerspectiveMatrix() const;

    // Returns the current position of the camera.
    glm::vec4 getPosition() const;

    // Returns the current 'look' vector for this camera.
    glm::vec4 getLook() const;

    // Returns the current 'up' vector for this camera (the 'V' vector).
    glm::vec4 getUp() const;

    // returns film to world matrix;
    virtual glm::mat4x4 getFilm2WorldMatrix() const;

    // Returns the currently set aspect ratio.
    float getAspectRatio() const;

    // Returns the currently set height angle.
    float getHeightAngle() const;

    // Move this camera to a new eye position, and orient the camera's axes given look and up
    // vectors.
    void orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up);

    // Sets the height angle of this camera.
    void setHeightAngle(float h);

    // Translates the camera along a given vector.
    void translate(const glm::vec4 &v);

    // Rotates the camera about the U axis by a specified number of degrees.
    void rotateU(float degrees);

    // Rotates the camera about the V axis by a specified number of degrees.
    void rotateV(float degrees);

    // Rotates the camera about the W axis by a specified number of degrees.
    void rotateW(float degrees);

    // Sets the near and far clip planes for this camera.
    void setClip(float nearPlane, float farPlane);

    // convert to radians
    float degree2Radians(float angle_degree) const;

    // convert to degree
    float radians2Degree(float angle_radian) const;

    // get corresponding matrices
    glm::mat4x4 get_M1() const;
    glm::mat4x4 get_M2() const;
    glm::mat4x4 get_M3() const;
    glm::mat4x4 get_M4() const;

    glm::mat4x4 get_M2_inv() const;
    glm::mat4x4 get_M3_inv() const;
    glm::mat4x4 get_M4_inv() const;

    // rotating
    static glm::mat4x4 getRotation(glm::vec4 r_point, glm::vec4 r_axis, float r_radian);
    static glm::mat4x4 getRotX(float r_radian);
    static glm::mat4x4 getRotY(float r_radian);
    static glm::mat4x4 getRotZ(float r_radian);
    static glm::mat4x4 getTrans(glm::vec4 trans_vec);
    static glm::mat4x4 getScale(glm::vec4 scale_vec);




private:
    glm::vec4 m_position;
    glm::vec4 m_look;
    glm::vec4 m_up;
    glm::vec4 m_u;
    glm::vec4 m_v;
    glm::vec4 m_w;
    float m_aspect;
    float m_tan_h_2;
    float m_tan_w_2;
    float m_h_angle_radian;
    float m_near;
    float m_far;



};

#endif // CAMTRANSCAMERA_H







