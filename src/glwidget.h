#ifndef glwidget_H
#define glwidget_H

#include "shape/Quad.h"

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include <QProgressBar>

#include "glm/glm/glm.hpp"

#include "camera/Camera.h"
#include "Shader.h"
#include "camera/CamtransCamera.h"
#include "scene/Basketball.h"
#include "shape/Shape.h"
#include "shape/Sphere.h"
#include "shape/Torus.h"
#include "shape/Cylinder.h"

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
    void setProgressBar(QProgressBar *pBar);

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



    void initBasketball();
    void initWall();
    void initHoop();
    void initBasketballStand();

    // Rendering methods.


    void renderWall();
    void renderHoop();
    void renderStand();

    void processCollision(Basketball *cur_basketball, int k);
    void processCollisionBall2Ball(Basketball *basketball_1, Basketball *basketball_2);
    void processCollisionBall2Wall(Basketball *cur_basketball, Wall cur_wall);
    void processCollisionBall2HoopBoard(Basketball *cur_basketball, HoopBoard cur_hoopBoard);
    void processScoring(Basketball *cur_basketball);

    void renderBasketball();





    Shader m_shader;
    Quad* m_quad;
    Sphere* m_sphere;
    Torus* m_torus;
    Cylinder* m_cylinder;

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
    QProgressBar * m_powerSlot;

    int m_power;

    int m_n_all;
    float m_wallsize;
    float m_hoopsize;
    float m_standsize;

    GLuint m_vaoID;
    GLuint m_vboID;
    GLuint m_textureId;
    GLuint m_basketballTextureId;
    GLuint m_boardId;
    GLuint m_normalId;
    GLuint m_courtId;
    GLuint m_skyId;

    glm::vec3 arrow_vel;

    const glm::vec4 eye = glm::vec4(0.0, 2.0, 3.0, 1.0);
    const glm::vec4 look = glm::vec4(0.0, 0.0, -1.0, 0.0);
    const glm::vec4 up = glm::vec4(0.0, 1.0, 0.0, 0.0);


    std::vector<Basketball *> m_basketballList;
    std::vector<Wall> m_wallList;
    std::vector<BasketballStand> m_basketballStandList;

    Hoop m_hoop;
    BackBoard m_backboard;
    std::vector<HoopBoard> m_hoopBoardList;

};

#endif // glwidget_H
