#ifndef glwidget_H
#define glwidget_H

#include "shape/Quad.h"

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>

#include "glm/glm/glm.hpp"

#include "camera/Camera.h"
#include "Shader.h"
#include "shape/Sphere.h"
#include "camera/CamtransCamera.h"
#include "scene/Basketball.h"
#include "shape/Shape.h"

#include "scene/SceneData.h"



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
    void setLabel_test(QLabel* label);

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

    void initBasketball();
    void initWall();

    // Rendering methods.
    void renderArrowSphere();
    void renderTarget();
    void renderTargetSphere();
    void renderRoom();
    void renderArrow();
    void renderBow();
    void renderQuad();
    void renderWall();

    void processCollision(Basketball *cur_basketball, int k);
    void processCollisionBall2Ball(Basketball *basketball_1, Basketball *basketball_2);
    void processCollisionBall2Wall(Basketball *cur_basketball, Wall cur_wall);


    void renderBasketball();



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

    CamtransCamera m_camera;
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
    QLabel * m_testLabel;
    bool m_canCollide;
    int m_n_all;
    float m_wallsize;

    GLuint m_vaoID;
    GLuint m_vboID;
    GLuint m_textureId;

    glm::vec3 arrow_vel;

    const glm::vec4 eye = glm::vec4(0.0, 2.0, 3.0, 1.0);
    const glm::vec4 look = glm::vec4(0.0, 0.0, -1.0, 0.0);
    const glm::vec4 up = glm::vec4(0.0, 1.0, 0.0, 0.0);


    std::vector<Basketball *> m_basketballList;
    std::vector<Wall> m_wallList;

};

#endif // glwidget_H
