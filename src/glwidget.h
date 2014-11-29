#ifndef glwidget_H
#define glwidget_H

#include "Quad.h"

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>

#include "glm/glm/glm.hpp"

#include "Camera.h"
#include "Shader.h"
#include "Sphere.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void updateSettings();
    void updateCamera();
    void rotateCamera(float deltaX, float deltaY);
    void setLabel(QLabel* label);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent ( QKeyEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );

protected slots:
    void tick();

private:
    // Initialization methods.
    void initShapes();
    void initTarget();
    void initSphere();

    // Rendering methods.
    void renderArrowSphere();
    void renderTarget();
    void renderTargetSphere();
    void renderRoom();
    void renderArrow();
    void renderBow();
    void renderQuad();

    void setTargetPosition(glm::vec3 pos);
    glm::vec3 getTargetPosition() { return m_targetPos; }
    glm::vec3 getArrowPosition() { return m_arrowPos; }

    float getTargetRadius() { return m_targetRadius; }
    float getArrowRadius() { return m_arrowRadius; }

    // This vector automatically contains the arrow's position x,y,z coordinates.
    glm::vec3 m_arrowPos;
    float m_arrowRadius;

    // This vector is initialized to 0,0,0.
    glm::vec3 m_targetPos;
    float m_targetRadius;

    Shader m_shader;
    Quad* m_quad;
    Sphere* m_sphere;

    LabCamera m_camera;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;

    // These variables are used for the game logic, which is already handled for you.
    QTimer m_timer;
    float m_fps;
    float m_increment;
    float m_angleX, m_angleY;
    float m_originalMouseX;
    float m_originalMouseY;
    bool m_firstPersonMode, m_fired;
    float m_firedAngleX, m_firedAngleY;
    float m_firedXDiff, m_firedZDiff;
    float m_xDiff, m_zDiff;
    int m_score;
    QLabel * m_scoreLabel;
    bool m_canCollide;
    int m_n_all;

    GLuint m_vaoID;
    GLuint m_vboID;
};

#endif // glwidget_H