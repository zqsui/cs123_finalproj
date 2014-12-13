#include "glwidget.h"
#include "Settings.h"
#include "Shader.h"
#include <iostream>

#include <GL/glew.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/string_cast.hpp"
#include "helper/Physics.h"
#include "helper/utils.h"


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent), m_timer(this), m_fps(60.0f), m_increment(0), m_angleX(0.0f),
      m_angleY(0.0f), m_xDiff(0.0f), m_zDiff(0.0f), m_arrowRadius(0.1), m_targetRadius(0.5),
      m_score(0), m_canCollide(false)
{

    // Set up the camera    
//    m_camera.eye.x = 0.0f, m_camera.eye.y = -m_arenaSize + m_ballHeight, m_camera.eye.z = 3.0f;
//    m_camera.center.x = 0.0f, m_camera.center.y = -m_arenaSize + m_ballHeight, m_camera.center.z = 0.0f;
//    m_camera.up.x = 0.0f, m_camera.up.y = 1.0f, m_camera.up.z = 0.0f;
//    m_camera.fovy = 45.0f, m_camera.near = 0.95f, m_camera.far = 1000.0f;

    m_camera.setClip(0.95f, 1000.0f);
    m_camera.setAspectRatio(1.0);
    m_camera.setHeightAngle(45.0);

//    const glm::vec4 eye = glm::vec4(0.0, -m_arenaSize + m_ballHeight, 3.0, 1.0);
//    const glm::vec4 look = glm::vec4(0.0, 0.0, -1.0, 0.0);
//    const glm::vec4 up = glm::vec4(0.0, 1.0, 0.0, 0.0);
    m_camera.orientLook(eye, look, up);

    arrow_vel = glm::vec3(0.0);
    // Set up 60 FPS draw loop
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));

    this->setMouseTracking(true);
    m_originalMouseX = -1;
    m_originalMouseY = -1;

    m_arrowPos = glm::vec3(0,-3.0f,0);
    m_targetPos = m_arrowPos;

    m_power = 1;

}


GLWidget::~GLWidget()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);

    for(unsigned int i=0;i<m_basketballList.size();i++)
        delete (m_basketballList[i]);

    delete m_quad;
    delete m_sphere;
    delete m_torus;
}


/**
 * Helper function to print out a matrix.
 */
void printMatrix( glm::mat4 matrix)
{
    for (int i=0; i<4; i++)
        std::cout << glm::to_string(matrix[i]) << std::endl;
    std::cout << std::endl;
}


/**
 * Initializes all vertex and normal data.
 */
void GLWidget::initShapes()
{
    m_quad = new Quad(m_shader);
    m_sphere = new Sphere(30, 30, 1 ,
                          m_shader.attrib("in_Position"),
                          m_shader.attrib("in_Normal"),
                          m_shader.attrib("texCoord") );
    m_torus = new Torus(30, 30, 10,
                          m_shader.attrib("in_Position"),
                          m_shader.attrib("in_Normal"),
                          m_shader.attrib("texCoord") );

    m_cylinder = new Cylinder(30, 30, 1,
                              m_shader.attrib("in_Position"),
                              m_shader.attrib("in_Normal"),
                              m_shader.attrib("texCoord") );
    //initTarget();
}

void GLWidget::initHoop(){
    m_hoopsize = 0.6;
    m_hoop.Ka = glm::vec3( 0.5f, 0.0f, 0.0f);
    m_hoop.mass = 999999;
    m_hoop.vel = glm::vec3(0.0);

    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 2.9f, -m_wallsize + m_hoopsize * 0.5f + 0.55f) );
    modelMat = glm::scale( modelMat, glm::vec3( m_hoopsize ) );
    modelMat = glm::rotate( modelMat, -90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    m_hoop.modelMat = modelMat;

    //
    glm::vec3 torus_center =glm::vec3(glm::translate(glm::mat4(1.0f),
                                           glm::vec3( 0.0f, 2.9f, -m_wallsize + m_hoopsize * 0.5f + 0.55f) )
                                    * glm::vec4(0.0, 0.0, 0.0, 1.0));


    //printVec3(torus_center);
    Plane tmpPlane;
    float width = 1.0f*m_hoopsize;
    float height = 0.2;
    //front outside
    tmpPlane.a = 0.0;
    tmpPlane.b = 0.0;
    tmpPlane.c = 1.0;
    modelMat = glm::mat4(1.0f);
    tmpPlane.centroid = torus_center + glm::vec3(0.0, 0.0, 0.5f*m_hoopsize);
    tmpPlane.d = -tmpPlane.centroid.z;
    modelMat = glm::translate(modelMat, tmpPlane.centroid);
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(1.0f, 0.0f, 0.0f);
    tmpPlane.height_vec = glm::vec3(0.0f, 1.0f, 0.0f);
    modelMat = glm::scale(modelMat, glm::vec3(tmpPlane.width/2, tmpPlane.height/2, 1.0));
    tmpPlane.normal = glm::vec3(0.0, 0.0, 1.0);
    tmpPlane.modelMat = modelMat;
    m_hoop.plane.push_back(tmpPlane);

    //left outside
    tmpPlane.a = 1.0;
    tmpPlane.b = 0.0;
    tmpPlane.c = 0.0;
    modelMat = glm::mat4(1.0f);
    tmpPlane.centroid = torus_center + glm::vec3(-0.5f*m_hoopsize, 0.0, 0.0);
    tmpPlane.d = -tmpPlane.centroid.x;
    modelMat = glm::translate(modelMat, tmpPlane.centroid);
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(0.0f, 0.0f, 1.0f);
    tmpPlane.height_vec = glm::vec3(0.0f, 1.0f, 0.0f);
    modelMat = glm::scale(modelMat, glm::vec3(tmpPlane.width/2, tmpPlane.height/2, 1.0));
    tmpPlane.normal = glm::vec3(-1.0, 0.0, 0.0);
    tmpPlane.modelMat = modelMat;
    m_hoop.plane.push_back(tmpPlane);

    //right outside
    tmpPlane.a = 1.0;
    tmpPlane.b = 0.0;
    tmpPlane.c = 0.0;
    modelMat = glm::mat4(1.0f);
    tmpPlane.centroid = torus_center + glm::vec3(0.5f*m_hoopsize, 0.0, 0.0);
    tmpPlane.d = -tmpPlane.centroid.x;
    modelMat = glm::translate(modelMat, tmpPlane.centroid);
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(0.0f, 0.0f, -1.0f);
    tmpPlane.height_vec = glm::vec3(0.0f, 1.0f, 0.0f);
    modelMat = glm::scale(modelMat, glm::vec3(tmpPlane.width/2, tmpPlane.height/2, 1.0));
    tmpPlane.normal = glm::vec3(1.0, 0.0, 0.0);
    tmpPlane.modelMat = modelMat;
    m_hoop.plane.push_back(tmpPlane);


    //top left
    float pipe_radius = 0.05*m_hoopsize/2;
    tmpPlane.a = 0.05;
    tmpPlane.b = 1.0;
    tmpPlane.c = 0.0;
    tmpPlane.centroid = torus_center + glm::vec3(-0.5f*m_hoopsize + pipe_radius, pipe_radius, 0.0);
    tmpPlane.d = -glm::dot(tmpPlane.centroid, glm::vec3(tmpPlane.a, tmpPlane.b, tmpPlane.c));
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(0.0f, 0.0f, 1.0f);
    tmpPlane.height_vec = glm::normalize(glm::vec3(1.0f, -0.05f, 0.0f));
    tmpPlane.normal = glm::normalize(glm::vec3(tmpPlane.a, tmpPlane.b, tmpPlane.c));
    m_hoop.plane.push_back(tmpPlane);

    //top right
    tmpPlane.a = -0.05;
    tmpPlane.b = 1.0;
    tmpPlane.c = 0.0;
    tmpPlane.centroid = torus_center + glm::vec3(0.5f*m_hoopsize - pipe_radius, pipe_radius, 0.0);
    tmpPlane.d = -glm::dot(tmpPlane.centroid, glm::vec3(tmpPlane.a, tmpPlane.b, tmpPlane.c));//-tmpPlane.centroid.y;
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(0.0f, 0.0f, 1.0f);
    tmpPlane.height_vec = glm::normalize(glm::vec3(1.0f, 0.05f, 0.0f));
    tmpPlane.normal = glm::normalize(glm::vec3(tmpPlane.a, tmpPlane.b, tmpPlane.c));
    m_hoop.plane.push_back(tmpPlane);


    //top front
    tmpPlane.a = 0.0;
    tmpPlane.b = 1.0;
    tmpPlane.c = -0.05;
    tmpPlane.centroid = torus_center + glm::vec3(0.0, pipe_radius, 0.5f*m_hoopsize - pipe_radius);
    printVec3(tmpPlane.centroid);
    tmpPlane.d = -glm::dot(tmpPlane.centroid, glm::vec3(tmpPlane.a, tmpPlane.b, tmpPlane.c));
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(1.0f, 0.0f, 0.0f);
    tmpPlane.height_vec = glm::normalize(glm::vec3(0.0f, -0.05f, -1.0f));
    tmpPlane.normal = glm::normalize(glm::vec3(tmpPlane.a, tmpPlane.b, tmpPlane.c));
    m_hoop.plane.push_back(tmpPlane);

    //left inside
    tmpPlane.a = 1.0;
    tmpPlane.b = 0.0;
    tmpPlane.c = 0.0;
    tmpPlane.centroid = torus_center + glm::vec3(-0.5f*m_hoopsize + pipe_radius*2, 0.0, 0.0);
    tmpPlane.d = -tmpPlane.centroid.x;
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(0.0f, 0.0f, 1.0f);
    tmpPlane.height_vec = glm::vec3(0.0f, 1.0f, 0.0f);
    tmpPlane.normal = glm::vec3(1.0, 0.0, 0.0);
    m_hoop.plane.push_back(tmpPlane);

    //right inside
    tmpPlane.a = 1.0;
    tmpPlane.b = 0.0;
    tmpPlane.c = 0.0;
    tmpPlane.centroid = torus_center + glm::vec3(0.5f*m_hoopsize - pipe_radius * 2, 0.0, 0.0);
    tmpPlane.d = -tmpPlane.centroid.x;
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(0.0f, 0.0f, -1.0f);
    tmpPlane.height_vec = glm::vec3(0.0f, 1.0f, 0.0f);
    modelMat = glm::scale(modelMat, glm::vec3(tmpPlane.width/2, tmpPlane.height/2, 1.0));
    tmpPlane.normal = glm::vec3(-1.0, 0.0, 0.0);
    m_hoop.plane.push_back(tmpPlane);

    //front inside
    tmpPlane.a = 0.0;
    tmpPlane.b = 0.0;
    tmpPlane.c = 1.0;
    tmpPlane.centroid = torus_center + glm::vec3(0.0, 0.0, 0.5f*m_hoopsize - pipe_radius * 2);
    tmpPlane.d = -tmpPlane.centroid.z;
    tmpPlane.width = width;
    tmpPlane.height = height;
    tmpPlane.width_vec = glm::vec3(1.0f, 0.0f, 0.0f);
    tmpPlane.height_vec = glm::vec3(0.0f, 1.0f, 0.0f);
    tmpPlane.normal = glm::vec3(0.0, 0.0, -1.0);
    m_hoop.plane.push_back(tmpPlane);

//    struct Plane{
//        float a, b, c, d;
//        float width;
//        float height;
//        glm::vec3 width_vec;
//        glm::vec3 height_vec;
//        glm::vec3 normal;
//        glm::vec3 centroid;
//    };
}

void GLWidget::initBasketballStand()
{
    BasketballStand tmpStand;
    m_standsize = 0.1f;
    float standmass = 999999;
    glm::vec3 standvel = glm::vec3(0.0);
    glm::mat4 modelMat = glm::mat4(1.0f);

    //vertical stand
    tmpStand.Ka = glm::vec3( 0.0f, 0.0f, 0.0f);
    tmpStand.mass = standmass;
    tmpStand.vel = standvel;
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 1.75f, -m_wallsize + m_standsize/2) );
    modelMat = glm::scale( modelMat, glm::vec3( m_standsize, 3.5f, m_standsize) );
    tmpStand.modelMat = modelMat;
    m_basketballStandList.push_back(tmpStand);


    //parallel stand
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 3.5f, -m_wallsize + 0.5f/2 - 0.01f) );
    modelMat = glm::rotate( modelMat, 90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( m_standsize, 0.5f, m_standsize) );
    tmpStand.modelMat = modelMat;

    m_basketballStandList.push_back(tmpStand);


    //backboard

//    m_backboard.Ka = glm::vec3( 1.0f, 1.0f, 1.0f);
//    m_backboard.mass = standmass;
//    m_backboard.vel = standvel;
//    modelMat = glm::mat4(1.0f);
//    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 3.5f, -m_wallsize + 0.5f ) );
//    modelMat = glm::scale( modelMat, glm::vec3( 0.8f ) );
//    m_backboard.modelMat = modelMat;
//    m_backboard.plane.a = 0;
//    m_backboard.plane.b = 0;
//    m_backboard.plane.c = 1;
//    m_backboard.plane.d = m_wallsize - 0.5f;


    // Hoop board
    // front quad
    HoopBoard tmpHoopBoard;
    Plane tmpPlane;
    glm::vec3 hoop_translation_vec;
    hoop_translation_vec = glm::vec3( 0.0f, 3.5f, -m_wallsize + 0.55f );
    glm::vec3 scale_vec = glm::vec3(1.17f, 0.8f, 1.0f);

    tmpHoopBoard.Ka = glm::vec3( 0.3f);
    tmpHoopBoard.mass = standmass;
    tmpHoopBoard.vel = standvel;
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, hoop_translation_vec);
    modelMat = glm::scale( modelMat, scale_vec );
    tmpHoopBoard.modelMat = modelMat;
    tmpPlane.a = 0;
    tmpPlane.b = 0;
    tmpPlane.c = 1;
    tmpPlane.d = -hoop_translation_vec.z;//m_wallsize - 0.55f;
    tmpPlane.normal = glm::vec3(0.0, 0.0, 1.0);
    tmpPlane.height_vec = glm::vec3(0.0, 1.0, 0.0);
    tmpPlane.width_vec = glm::vec3(1.0, 0.0, 0.0);
    tmpPlane.centroid = hoop_translation_vec;
    tmpPlane.width = scale_vec.x * 2;
    tmpPlane.height = scale_vec.y * 2;
    tmpHoopBoard.plane = tmpPlane;
    tmpHoopBoard.object_type = PRIMITIVE_QUAD;
    m_hoopBoardList.push_back(tmpHoopBoard);

    // back quad       
    hoop_translation_vec = glm::vec3( 0.0f, 3.5f, -m_wallsize + 0.5f );
    tmpHoopBoard.Ka = glm::vec3( 0.3f);
    tmpHoopBoard.mass = standmass;
    tmpHoopBoard.vel = standvel;
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, hoop_translation_vec);
    modelMat = glm::scale( modelMat, scale_vec);
    modelMat = glm::rotate(modelMat, 180.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    tmpHoopBoard.modelMat = modelMat;
    tmpPlane.a = 0;
    tmpPlane.b = 0;
    tmpPlane.c = 1;
    tmpPlane.d = -hoop_translation_vec.z;//m_wallsize - 0.5f;
    tmpPlane.normal = glm::vec3(0.0, 0.0, -1.0);
    tmpPlane.height_vec = glm::vec3(0.0, 1.0, 0.0);
    tmpPlane.width_vec = glm::vec3(-1.0, 0.0, 0.0);
    tmpPlane.centroid = hoop_translation_vec;
    tmpPlane.width = scale_vec.x * 2;
    tmpPlane.height = scale_vec.y * 2;
    tmpHoopBoard.plane = tmpPlane;
    tmpHoopBoard.object_type = PRIMITIVE_QUAD;
    m_hoopBoardList.push_back(tmpHoopBoard);



}


void GLWidget::initBasketball()
{
    glm::vec3 pos = glm::vec3( -m_firedXDiff, 2, -m_firedZDiff );
    m_basketballList.push_back(new Basketball(pos, 1, 0.5 * 0.3));
}

void GLWidget::initWall()
{
    Wall tmpWall;
    glm::vec3 Ka;

    m_wallsize = 7;

    float wallmass = 999999;
    glm::vec3 wallvel = glm::vec3(0.0);

//    // Ceiling
    Ka =glm::vec3(0.1);

    glm::mat4 modelMat = glm::mat4(1.0f);
    tmpWall.Ka =  5.0f * Ka;
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, m_wallsize, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( m_wallsize ) );
    modelMat = glm::rotate(modelMat, 90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    tmpWall.modelMat = modelMat;
    tmpWall.plane.a = 0.0;
    tmpWall.plane.b = 1.0;
    tmpWall.plane.c = 0.0;
    tmpWall.plane.d = -m_wallsize;
    tmpWall.mass = wallmass;
    tmpWall.vel = wallvel;
    tmpWall.normal = glm::vec3(0.0, -1.0, 0.0);
    tmpWall.wallType = WALL_SKY;
    m_wallList.push_back(tmpWall);

    // Back
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, m_wallsize ) );
    modelMat = glm::scale( modelMat, glm::vec3( m_wallsize ) );
    modelMat = glm::rotate(modelMat, 180.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    tmpWall.Ka = Ka;
    tmpWall.modelMat = modelMat;
    tmpWall.plane.a = 0.0;
    tmpWall.plane.b = 0.0;
    tmpWall.plane.c = 1.0;
    tmpWall.plane.d = -m_wallsize;
    tmpWall.mass = wallmass;
    tmpWall.vel = wallvel;
    tmpWall.normal = glm::vec3(0.0, 0.0, -1.0);
    tmpWall.wallType = WALL_BRICK;
    m_wallList.push_back(tmpWall);

    // Right
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( m_wallsize, 0.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( m_wallsize ) );
    modelMat = glm::rotate(modelMat, -90.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    tmpWall.Ka = Ka;
    tmpWall.modelMat = modelMat;
    tmpWall.plane.a = 1.0;
    tmpWall.plane.b = 0.0;
    tmpWall.plane.c = 0.0;
    tmpWall.plane.d = -m_wallsize;
    tmpWall.mass = wallmass;
    tmpWall.vel = wallvel;
    tmpWall.normal = glm::vec3(-1.0, 0.0, 0.0);
    tmpWall.wallType = WALL_BRICK;
    m_wallList.push_back(tmpWall);

    // Left
   modelMat = glm::mat4(1.0f);
   modelMat = glm::translate( modelMat, glm::vec3( -m_wallsize, 0.0f, 0.0f ) );
   modelMat = glm::scale( modelMat, glm::vec3( m_wallsize) );
   modelMat = glm::rotate(modelMat, 90.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
   tmpWall.Ka = Ka;
   tmpWall.modelMat = modelMat;
   tmpWall.plane.a = 1.0;
   tmpWall.plane.b = 0.0;
   tmpWall.plane.c = 0.0;
   tmpWall.plane.d = m_wallsize;
   tmpWall.mass = wallmass;
   tmpWall.vel = wallvel;
   tmpWall.normal = glm::vec3(1.0, 0.0, 0.0);
   tmpWall.wallType = WALL_BRICK;
   m_wallList.push_back(tmpWall);

    //front

   modelMat = glm::mat4(1.0f);
   modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, -m_wallsize ) );
   modelMat = glm::scale( modelMat, glm::vec3( m_wallsize ) );
   tmpWall.Ka = Ka;
   tmpWall.modelMat = modelMat;
   tmpWall.plane.a = 0.0;
   tmpWall.plane.b = 0.0;
   tmpWall.plane.c = 1.0;
   tmpWall.plane.d = m_wallsize;
   tmpWall.mass = wallmass;
   tmpWall.vel = wallvel;
   tmpWall.normal = glm::vec3(0.0, 0.0, 1.0);
   tmpWall.wallType = WALL_BRICK;
   m_wallList.push_back(tmpWall);

   //ground

   //m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
   modelMat = glm::mat4(1.0f);
   modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, 0.0f ) );
   modelMat = glm::scale( modelMat, glm::vec3( m_wallsize, m_wallsize, m_wallsize) );
   modelMat = glm::rotate(modelMat, -90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
   tmpWall.Ka = Ka;
   tmpWall.modelMat = modelMat;
   tmpWall.plane.a = 0.0;
   tmpWall.plane.b = 1.0;
   tmpWall.plane.c = 0.0;
   tmpWall.plane.d = 0.0;
   tmpWall.mass = wallmass;
   tmpWall.vel = wallvel;
   tmpWall.normal = glm::vec3(0.0, 1.0, 0.0);
   tmpWall.wallType = WALL_GROUND;
   m_wallList.push_back(tmpWall);
}
/**
 * Initializes the target's vertex and normal data.
 */
void GLWidget::initTarget()
{
    GLuint positionAttrib = m_shader.attrib("in_Position"); // Index of the vertex position attribute.
    GLuint normalAttrib = m_shader.attrib("in_Normal"); // Index of the vertex normal attribute.

    // TODO: Implement this method.
    int n_tessel = 6;
    float r = 0.5;
    float theta = 2*M_PI/n_tessel;
    m_n_all = (n_tessel+2)*3*2;
    GLfloat *vertexBufferData = new GLfloat[m_n_all];

    int i;
    for(i=0;i<5;i++)
        vertexBufferData[i] = 0.0f;
    vertexBufferData[5] = -1.0f;
    int index;
    for(i=0;i<n_tessel;i++)
    {
        index = 6 + i*6;
        vertexBufferData[index] = r *cos(theta*i);
        vertexBufferData[index+1] = r * sin(-theta*i);
        vertexBufferData[index+2] = 0.0f;
        vertexBufferData[index+3] = 0.0f;
        vertexBufferData[index+4] = 0.0f;
        vertexBufferData[index+5] = -1.0f;
    }

    index = 6 + i*6;
    vertexBufferData[index] = r *cos(theta*i);
    vertexBufferData[index+1] = r * sin(-theta*i);
    vertexBufferData[index+2] = 0.0f;
    vertexBufferData[index+3] = 0.0f;
    vertexBufferData[index+4] = 0.0f;
    vertexBufferData[index+5] = -1.0f;

    // Step 2: initialize and bind a Vertex Array Object -- see glGenVertexArrays and glBindVertexArray
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);


    // Step 3: initialize and bind a buffer for your vertex data -- see glGenBuffers and glBindBuffer

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    // Step 4: Send your vertex data to the GPU -- see glBufferData
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* m_n_all, vertexBufferData, GL_STATIC_DRAW);

    // Step 5: Expose the vertices to other OpenGL components (namely, shaders)
    //         -- see glEnableVertexAttribArray and glVertexAttribPointer
    glEnableVertexAttribArray(positionAttrib);
    glEnableVertexAttribArray(normalAttrib);
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (void*) 0);
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*6, (void*) (sizeof(GLfloat) * 3));

    // Step 6: Clean up -- unbind the buffer and vertex array.
    //         It is a good habit to leave the state of OpenGL the way you found it
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}



void GLWidget::renderWall()
{
    for(unsigned int i = 0; i < m_wallList.size();i++)
    {
        Wall cur_wall = m_wallList[i];
        glm::vec3 Ka = cur_wall.Ka;
        glm::mat4 modelMat =cur_wall.modelMat;
        int walltype = cur_wall.wallType;
        m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
        m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
//        std::cout<<walltype<<std::endl;
        switch (walltype) {
        case WALL_BRICK:
            glActiveTexture(GL_TEXTURE0); // Set the active texture to texture 0.
            glBindTexture(GL_TEXTURE_2D, m_textureId);
            glUniform1i(m_shader.uniformLocation("textureSampler"), 0);

            glActiveTexture(GL_TEXTURE1); // Set the active texture to texture 1.
            glBindTexture(GL_TEXTURE_2D, m_normalId);
            glUniform1i(m_shader.uniformLocation("normalSampler"), 1);
            glUniform1i(m_shader.uniformLocation("isBumpMapping"), settings.showIntersectSpheres);
            break;
        case WALL_SKY:
            glActiveTexture(GL_TEXTURE0); // Set the active texture to texture 0.
            glBindTexture(GL_TEXTURE_2D, m_skyId);
            glUniform1i(m_shader.uniformLocation("textureSampler"), 0);
            glUniform1i(m_shader.uniformLocation("isBumpMapping"), 0);
            break;
        case WALL_GROUND:
            glActiveTexture(GL_TEXTURE0); // Set the active texture to texture 0.
            glBindTexture(GL_TEXTURE_2D, m_courtId);
            glUniform1i(m_shader.uniformLocation("textureSampler"), 0);
            glUniform1i(m_shader.uniformLocation("isBumpMapping"), 0);
            break;
        default:
            break;
        }
        m_quad->draw();

    }
    glUniform1i(m_shader.uniformLocation("isBumpMapping"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLWidget::renderHoop()
{
    glm::vec3 Ka = m_hoop.Ka;
    glm::mat4 modelMat =m_hoop.modelMat;
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    m_torus->draw();


//    for(unsigned int i = 0; i< m_hoop.plane.size();i++)
//    {
//        Plane cur_plane = m_hoop.plane[i];
//        modelMat = cur_plane.modelMat;
//        m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
//        m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
//        m_quad->draw();
//    }
}


void GLWidget::renderStand()
{
    for(unsigned int i = 0; i < m_basketballStandList.size(); i++)
    {
        BasketballStand cur_stand = m_basketballStandList[i];
        glm::vec3 Ka = cur_stand.Ka;
        glm::mat4 modelMat =cur_stand.modelMat;
        m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
        m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
        m_cylinder->draw();
    }

//    glm::vec3 Ka = m_backboard.Ka;
//    glm::mat4 modelMat =m_backboard.modelMat;
//    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
//    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
//    m_quad->draw();

    for(int i = 0; i < m_hoopBoardList.size();i++)
    {
        HoopBoard cur_hoopBoard = m_hoopBoardList[i];
        glm::vec3 Ka = cur_hoopBoard.Ka;
        glm::mat4 modelMat = cur_hoopBoard.modelMat;
        m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
        m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
        switch (cur_hoopBoard.object_type) {
        case PRIMITIVE_QUAD:
            glActiveTexture(GL_TEXTURE0); // Set the active texture to texture 0.
            m_shader.setUniform("textureSampler", Shader::INT, 0);
            glBindTexture(GL_TEXTURE_2D, m_boardId);
            m_quad->draw();
            glBindTexture(GL_TEXTURE_2D, 0);
            break;
        default:
            break;
        }
//        std::cout<<cur_hoopBoard.plane.centroid.x<<" "<<cur_hoopBoard.plane.centroid.y<<" "<<cur_hoopBoard.plane.centroid.z<<std::endl;
//        std::cout<<cur_hoopBoard.plane.width<<std::endl;
//        std::cout<<cur_hoopBoard.plane.height<<std::endl;

    }
}



/**
 * Renders the target and sets its position via setTargetPosition.
 * You have to fill in this method.
 */
void GLWidget::renderTarget()
{
    // Sets a lighting uniform to make target appear orange.
    glm::vec3 Ka = glm::vec3( 1.0f, 0.5f, 0.0f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );

    // TODO: Implement this method.

    glm::mat4 targetModelMat;
    //setTargetPosition(glm::vec3(0, 0, 0));
    //targetModelMat = glm::translate(m_targetPos, glm::vec3(0, 0, 3));
    //targetModelMat =
    targetModelMat =glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 3.0));
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &targetModelMat[ 0 ][ 0 ]);
    setTargetPosition(glm::vec3(0, 1, 3.0));
    //targetModelMat = glm::translate(targetModelMat, glm::vec3(0, 0, 3));

    glBindVertexArray(m_vaoID);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_n_all);
    glBindVertexArray(0);

}


/**
 * Renders the intersection sphere for the arrow.
 * You need to fill in this method.
 */
void GLWidget::renderArrowSphere()
{
    // Sets a lighting uniform to make sphere appear gray.
    glm::vec3 Ka = glm::vec3( 0.5f, 0.5f, 0.5f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );

    // TODO: Implement this method.

    glm::mat4 arrowModelMat;
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowModelMat[0][0]);

    glm::mat4 arrowSphereMat;
    //float scale = getArrowRadius();
    //arrowSphereMat = glm::scale(glm::mat4(1.0), glm::vec3(scale, scale, scale));
    //arrowSphereMat = glm::translate(arrowSphereMat, getArrowPosition());
    //arrowSphereMat = glm::translate(glm::mat4(1.0), getArrowPosition());

    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowSphereMat[ 0 ][ 0 ]);
    m_sphere->draw();
}


/**
 * Render the intersection sphere for the target.
 * You need to fill in this method.
 */
void GLWidget::renderTargetSphere()
{
    // Sets a lighting uniform to make sphere appear gray.
    glm::vec3 Ka = glm::vec3( 0.5f, 0.5f, 0.5f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );

    // TODO: Implement this method.
    glm::mat4 targetSphereMat;
    float scale = getTargetRadius();
    targetSphereMat = glm::scale(glm::translate(glm::mat4(1.0), getTargetPosition()), glm::vec3(scale, scale, scale));

    m_shader.setUniform( "M_Matrix", Shader::MAT4, &targetSphereMat[ 0 ][ 0 ]);
    m_sphere ->draw();
}


/**
 * Called once at GL initialization time to setup OpenGL states.
 */
void GLWidget::initializeGL()
{
    glewExperimental = GL_TRUE;
    int err;
    if( ( err = glewInit() ) != GLEW_OK )
    {
        printf(" Error initializing GLEW: %s\n", glewGetErrorString( err ) );
    }

    // Enable depth testing, so that objects are occluded based on depth instead of drawing order.
    glEnable(GL_DEPTH_TEST);

    // Enable back-face culling, meaning only the front side of every face is rendered.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Specify that the front face is represented by vertices in counterclockwise order. (This
    // is the default.)
    glFrontFace(GL_CCW);

    // Load the initial settings.
    m_shader.loadVertexShader( "../cs123_finalproj/ADS/ADS.vert" );
    m_shader.loadFragmentShader( "../cs123_finalproj/ADS/ADS.frag" );
    m_shader.compile();
    m_shader.use();

    m_textureId = m_shader.loadTexture("../cs123_finalproj/textures/brick.jpg");
    m_basketballTextureId = m_shader.loadTexture("../cs123_finalproj/textures/BasketballColor.jpg");
    m_boardId = m_shader.loadTexture("../cs123_finalproj/textures/Board2.jpg");
    m_normalId = m_shader.loadTexture("../cs123_finalproj/textures/brickBump.jpg");
    m_courtId = m_shader.loadTexture("../cs123_finalproj/textures/court.jpg");
    m_skyId = m_shader.loadTexture("../cs123_finalproj/textures/sky.jpg");


    // Set lighting properties.
    glm::vec3 La = glm::vec3( 0.5f );
    m_shader.setUniform( "La", Shader::VEC3, &La );
    glm::vec3 Lpos = glm::vec3( 5.0f, 5.0f, 5.0f );
    m_shader.setUniform( "Lpos", Shader::VEC3, &Lpos );
    glm::vec3 Ld = glm::vec3( 1.0f, 1.0f, 1.0f );
    m_shader.setUniform( "Ld", Shader::VEC3, &Ld );
    updateSettings();
    updateCamera();
    initShapes();
    initBasketball();
    initWall();
    initHoop();
    initBasketballStand();

}


/**
 * The main drawing method which will be called 30 frames per second.
 */
void GLWidget::paintGL()
{
    // If we haven't fired yet, update the angles so that the arrow's angles and position to
    // match the camera's.

    m_firedAngleX = m_angleX;
    m_firedAngleY = m_angleY;
    m_firedXDiff = m_xDiff;
    m_firedZDiff = m_zDiff;


    // Clear the color and depth buffers to the current glClearColor
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

//    renderTarget();

//    renderBow();

//    renderArrow();



    renderWall();
    renderHoop();
    renderStand();

    glActiveTexture(GL_TEXTURE0); // Set the active texture to texture 0.
    glBindTexture(GL_TEXTURE_2D, m_basketballTextureId);
    m_shader.setUniform("normalSampler", Shader::INT, 0);
    renderBasketball();
    glBindTexture(GL_TEXTURE_2D, 0);

    //renderRoom();

    //Render intersection spheres
//    if(m_canCollide && settings.showIntersectSpheres)
//    {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//        glm::vec3 Ka = glm::vec3( 0.5f );
//        m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
//        renderTargetSphere();

//        renderArrowSphere();

//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    }
}


void GLWidget::renderBasketball()
{
//    std::cout<<m_basketballList.size()<<std::endl;
    for(unsigned int i = 0; i<m_basketballList.size();i++)
    {
        float delta_t = 0.5f/(float)m_fps;
        Basketball *cur_basketball = m_basketballList[i];
        float scale = cur_basketball->getRadius() * 2;

        glm::vec3 cur_pos = glm::vec3( -m_firedXDiff, 2, -m_firedZDiff );
//        std::cout<<cur_pos.x<<" "<<cur_pos.y<<" "<<cur_pos.z<<std::endl;
        glm::mat4 basketballModelMat0 = glm::mat4( 1.0f );
        basketballModelMat0 = glm::translate(basketballModelMat0, cur_pos);
        glm::vec4 new_eye = eye + glm::vec4(-m_firedXDiff, 0.0, -m_firedZDiff, 0.0);
        glm::mat4 rotateX = m_camera.getRotation(new_eye, up,
                                                 m_camera.degree2Radians(-m_firedAngleX));
        basketballModelMat0 =  rotateX * basketballModelMat0;
        glm::vec4 r_axis = rotateX * glm::vec4(1.0, 0.0, 0.0, 0.0);
        basketballModelMat0 = m_camera.getRotation(new_eye, r_axis,
                                                   m_camera.degree2Radians(-m_firedAngleY))
                * basketballModelMat0;
        basketballModelMat0 = basketballModelMat0 * m_camera.getScale(glm::vec4(scale));
        glm::vec4 new_pos = basketballModelMat0 * glm::vec4(0.0, 0.0, 0.0, 1.0);
        cur_pos = glm::vec3(new_pos);

        if (!cur_basketball->isFired())
        {
            glm::vec3 cur_vel = glm::normalize(glm::transpose(glm::inverse(glm::mat3x3(basketballModelMat0))) *
                glm::vec3(0.0f, 0.0f, -1.0f));
            float vel_power =(float)cur_basketball->getPower()/3.0f;
            cur_vel = cur_vel * vel_power;
            cur_basketball->updateVel(cur_vel);
            cur_basketball->updatePos(cur_pos);

//            std::cout<<vel_power<<std::endl;
//            glm::vec3 rotate_axis = glm::cross(cur_vel, glm::vec3(0.0, -1.0, 0.0));

//            std::cout<<"---"<<std::endl;
//            printMatrix(basketballModelMat0);
//            basketballModelMat0 = m_camera.getRotation(glm::vec4(cur_pos, 0.0), glm::vec4(rotate_axis, 0.0),
//                                                       10 * glm::length(cur_vel)) * basketballModelMat0;
//            printMatrix(basketballModelMat0);
//            glm::mat4 tmp = m_camera.getRotation(glm::vec4(cur_pos, 0.0), glm::vec4(rotate_axis, 0.0),
//                                                 10 * glm::length(cur_vel));

//            printMatrix(tmp);


            // printVec3(cur_pos);
        }
        else if(!cur_basketball->isDisappeared())
        {            
            glm::vec3 accel = glm::vec3(0.0, -GRAVITY, 0.0);
            glm::vec3 next_vel = accelVel(cur_basketball->getVel(), accel, delta_t);
            glm::vec3 delta_s = computeDisplacement(cur_basketball->getVel(),
                                                    accel, delta_t);
            cur_pos = cur_basketball->getPos() + delta_s;
            cur_basketball->updateVel(next_vel);
            cur_basketball->updatePos(cur_pos);
            //cur_pos = cur_basketball->getPos() + cur_basketball->getVel() * delta_t;

            glm::vec3 rotate_axis = glm::cross(next_vel, glm::vec3(0.0, -1.0, 0.0));

            basketballModelMat0 = glm::mat4(1.0f);
//            basketballModelMat0 = glm::translate(glm::mat4(1.0f), cur_pos);
//            basketballModelMat0 = glm::rotate(basketballModelMat0, glm::length(next_vel), rotate_axis);

            basketballModelMat0 = glm::translate(basketballModelMat0, cur_pos);
            basketballModelMat0 = glm::scale(basketballModelMat0, glm::vec3(scale));
            float cur_spin;
//            if(glm::length(cur_basketball->getVel()) > 5)
                cur_spin = -1.0f * (float)cur_basketball->getSpin()/10.0f;// * glm::length(cur_basketball->getVel());
//            else
//                cur_spin = 0;
//            std::cout<<cur_spin<<std::endl;
            basketballModelMat0 = m_camera.getRotation(glm::vec4(cur_pos, 0.0), glm::vec4(rotate_axis, 0.0),
                                              cur_spin) * basketballModelMat0;
            cur_basketball->updateSpin(cur_basketball->getSpin() + 1);


            processCollision(cur_basketball, i);

            if(!cur_basketball->isScored())
                processScoring(cur_basketball);

//            std::cout<<cur_pos.y<<std::endl;
            if(EQ(glm::length(cur_basketball->getVel()), 0) && EQ(cur_pos.y, 0.149521))
                cur_basketball->setDisappear();
        }
        else
        {
            // If disappeared, do nothing;
        }


        glm::vec3 Ka = glm::vec3(0.2f);
        m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
        m_shader.setUniform( "M_Matrix", Shader::MAT4, &basketballModelMat0[ 0 ][ 0 ] );


        if(!cur_basketball->isDisappeared()){
            m_sphere->draw();
        }
    }
}


void GLWidget::processScoring(Basketball *cur_basketball)
{
    glm::vec3 hoop_pos = glm::vec3(m_hoop.modelMat * glm::vec4(0.0, 0.0, 0.0, 1.0));
    glm::vec3 cur_pos = cur_basketball->getPos();
//    std::cout<<"---"<<std::endl;
//    std::cout<<point2PointDist(hoop_pos, cur_pos)<<std::endl;
//    std::cout<<fabs(cur_pos.y - hoop_pos.y)<<std::endl;

    if((point2PointDist(hoop_pos, cur_pos) < m_hoopsize * 0.45 - 0.149521)
            && fabs(cur_pos.y - hoop_pos.y) < 0.2)
    {
        glm::vec3 cur_vel = cur_basketball->getVel();
        cur_vel.x = 0.5 * rand()/RAND_MAX;
        cur_vel.z = 0.5 * rand()/RAND_MAX;
        cur_basketball->updateVel(cur_vel);
        cur_basketball->setScored();

        m_scoreLabel->setText("Score: " + QString::number(++m_score));
        m_hoopBoardList[0].Ka = glm::vec3(1.0 * rand()/RAND_MAX, 1.0 * rand()/RAND_MAX, 1.0 * rand()/RAND_MAX);


//        std::cout<<"score"<<std::endl;
//        printVec3(hoop_pos);
//        printVec3(cur_basketball->getPos());
//        std::cout<<point2PointDist(hoop_pos, cur_basketball->getPos())<<std::endl;
    }
}

void GLWidget::processCollision(Basketball *cur_basketball, int k)
{
    for(unsigned int i = k+1;i < m_basketballList.size() - 1;i++)
    {
        Basketball *tmp = m_basketballList[i];
        if(!tmp->isDisappeared())
            processCollisionBall2Ball(cur_basketball, m_basketballList[i]);
    }


    for(unsigned int i = 0; i < m_wallList.size(); i++)
        processCollisionBall2Wall(cur_basketball, m_wallList[i]);

    for(unsigned int i = 0; i < m_hoopBoardList.size();i++)
    {
        HoopBoard cur_hoopBoard = m_hoopBoardList[i];
        processCollisionBall2HoopBoard(cur_basketball, cur_hoopBoard);
    }

    for(unsigned int i = 0; i < m_hoop.plane.size();i++)
    {
        Plane cur_plane = m_hoop.plane[i];
        HoopBoard tmpHoopBoard;
        tmpHoopBoard.plane = cur_plane;
        tmpHoopBoard.mass = 999999;
        tmpHoopBoard.vel = glm::vec3(0.0f);
        tmpHoopBoard.object_type = PRIMITIVE_QUAD;

        processCollisionBall2HoopBoard(cur_basketball, tmpHoopBoard);
    }

}

void GLWidget::processCollisionBall2Plane(Basketball *cur_basketball, Plane cur_plane)
{


////    Plane cur_plane = cur_hoopBoard.plane;
//    float dist = point2PlaneDist(cur_basketball->getPos(), cur_plane);
//    if(cur_basketball->getRadius() - dist > EPSILON)
//    {
//      glm::vec3 intersectVerticalPoint =
//            point2PlaneIntersectionPoint(cur_basketball->getPos(), cur_plane, cur_plane.normal);
//      if(isPointInPlane(intersectVerticalPoint, cur_plane))
//      {
////          glm::vec3 dir = -cur_plane.normal;
////          glm::vec3 pos_new = cur_basketball->getPos() -
////                  1.0f * (cur_basketball->getRadius()  - dist) * glm::normalize(dir);
////          cur_basketball->updatePos(pos_new);

////          glm::vec3 ball_vel = cur_basketball->getVel();
////          glm::vec3 quad_vel = cur_hoopBoard.vel;
////          float ball_mass = cur_basketball->getMass();
////          float quad_mass = cur_hoopBoard.mass;
////          momentumTheory(ball_mass, ball_vel, quad_mass, quad_vel, dir);
////          float scale_v;
////          float vel_length = glm::length(ball_vel);
////          if(vel_length<0.5)
////              scale_v = 0;
////          else if(vel_length < 1.5)
////              scale_v = 0.5;
////          else
////              scale_v = 0.9;
////          ball_vel *= scale_v;
////          cur_basketball->updateVel(ball_vel);
//      }
//      else
//          return;
//    }
//    else
//        return;

}



void GLWidget::processCollisionBall2Ball(Basketball *basketball_1, Basketball *basketball_2)
{
    float dist = point2PointDist(basketball_1->getPos(), basketball_2->getPos());

//    if(EQ(dist, 0))
//        return;

    float radius_sum = basketball_1->getRadius() + basketball_2->getRadius();

    if(radius_sum - dist > EPSILON)
    {
        glm::vec3 dir = basketball_2->getPos() - basketball_1->getPos();
        glm::vec3 pos1_new = basketball_1->getPos() - 1.0f * (radius_sum - dist) * glm::normalize(dir);
        //glm::vec3 pos2_new = basketball_2->getPos() + 1.0f/2.0f * (radius_sum - dist) * glm::normalize(dir);

        basketball_1->updatePos(pos1_new);
        //basketball_2->updatePos(pos2_new);

        glm::vec3 v1 = basketball_1->getVel();
        glm::vec3 v2 = basketball_2->getVel();

        momentumTheory(basketball_1->getMass(), v1,
                       basketball_2->getMass(), v2,
                       dir);
//        float scale_v = 0.9;
//        v1 *= scale_v;
//        v2 *= scale_v;
        basketball_1->updateVel(v1);
        basketball_2->updateVel(v2);
    }
    else
    {
        return;
    }
}

void GLWidget::processCollisionBall2Wall(Basketball *cur_basketball, Wall cur_wall)
{
    float dist = point2PlaneDist(cur_basketball->getPos(), cur_wall.plane);
//    std::cout<<dist << ' ' <<EPSILON + cur_basketball->getRadius()<<std::endl;

    if(cur_basketball->getRadius() - dist > EPSILON)
    {
        glm::vec3 dir = -cur_wall.normal;
        glm::vec3 pos_new = cur_basketball->getPos() - 1.0f * (cur_basketball->getRadius()  - dist) * glm::normalize(dir);
        cur_basketball->updatePos(pos_new);

        glm::vec3 ball_vel = cur_basketball->getVel();
        glm::vec3 wall_vel = cur_wall.vel;
        float ball_mass = cur_basketball->getMass();
        float wall_mass = cur_wall.mass;
//        std::cout<<"before momentum theory"<<std::endl;
//        std::cout<<glm::length(ball_vel)<<std::endl;
        momentumTheory(ball_mass, ball_vel, wall_mass, wall_vel, dir);
//        std::cout<<"after momentum theory"<<std::endl;
//        std::cout<<glm::length(ball_vel)<<std::endl;
        float scale_v;
        float vel_length = glm::length(ball_vel);
        if(vel_length<1.5)
            scale_v = 0;
        else if(vel_length < 2)
            scale_v = 0.5;
        else
            scale_v = 0.9;
        ball_vel *= scale_v;
//        std::cout<<"after scaling"<<std::endl;
//        std::cout<<glm::length(ball_vel)<<std::endl;
        cur_basketball->updateVel(ball_vel);
    }
    else
    {
        return;
    }
}


void  GLWidget::processCollisionBall2HoopBoard(Basketball *cur_basketball, HoopBoard cur_hoopBoard)
{
    switch(cur_hoopBoard.object_type){
    case PRIMITIVE_QUAD:
    {
        Plane cur_plane = cur_hoopBoard.plane;
        float dist = point2PlaneDist(cur_basketball->getPos(), cur_plane);
        if(cur_basketball->getRadius() - dist > EPSILON)
        {
          glm::vec3 intersectVerticalPoint =
                point2PlaneIntersectionPoint(cur_basketball->getPos(), cur_plane, cur_plane.normal);
          if(isPointInPlane(intersectVerticalPoint, cur_plane))
          {
              glm::vec3 dir = -cur_plane.normal;
              glm::vec3 pos_new = cur_basketball->getPos() -
                      1.0f * (cur_basketball->getRadius()  - dist) * glm::normalize(dir);
              cur_basketball->updatePos(pos_new);

              glm::vec3 ball_vel = cur_basketball->getVel();
              glm::vec3 quad_vel = cur_hoopBoard.vel;
              float ball_mass = cur_basketball->getMass();
              float quad_mass = cur_hoopBoard.mass;
              momentumTheory(ball_mass, ball_vel, quad_mass, quad_vel, dir);
              float scale_v;
              float vel_length = glm::length(ball_vel);
              if(vel_length<0.5)
                  scale_v = 0;
              else if(vel_length < 1.5)
                  scale_v = 0.5;
              else
                  scale_v = 0.9;
              ball_vel *= scale_v;
              cur_basketball->updateVel(ball_vel);
          }
          else
          {
              return;
          }
        }
        else
            return;
        break;
    }
    default:
        break;
    }
}



/**
 * This method renders an arrow created via composition of glu objects
 */
void GLWidget::renderArrow()
{
    // Get the time
    float time = 5.0f * m_increment / (float) m_fps;

    // Start arrow off at fired position i.e. camera position when the arrow was fired or current
    // camera position if it hasn't been fired.
    m_arrowPos =  glm::vec3( -m_firedXDiff, 2, -m_firedZDiff );
    // m_arrowPos =  glm::vec3( 0.0f, -3.0f, 0.0f );
//    std::cout << m_firedXDiff << ' ' << -m_arenaSize + m_ballHeight << ' ' << m_firedZDiff << std::endl;



    // Set the velocity to reflect the rotation transforms we do to render the arrow.
    // We keep variables for all the values we need for this to simplify the velocity vector.
//    double cx = cos( -m_firedAngleX * M_PI / 180.0f );
//    double sx = sin( -m_firedAngleX * M_PI / 180.0f );
//    double cy = cos( m_firedAngleY * M_PI / 180.0f );
//    double omcy = 1.0f - cy;
//    double sy = sin( m_firedAngleY * M_PI / 180.0f );

//    double cmx = cos( M_PI * m_firedAngleX / 180.0f );
//    double smx = sin( M_PI * m_firedAngleX / 180.0f );



    //arrowModelMat0 = glm::translate( arrowModelMat0, m_arrowPos );
    //
//    arrowModelMat0 = glm::scale( arrowModelMat0, glm::vec3( 0.075f ) );
//    arrowModelMat0 = glm::translate( arrowModelMat0, m_arrowPos );
//    arrowModelMat0 = glm::rotate( arrowModelMat0, m_firedAngleY, glm::vec3( cmx, 0.0f, smx ) );
//    arrowModelMat0 = glm::rotate( arrowModelMat0, -m_firedAngleX, glm::vec3( 0.0f, 1.0f, 0.0f ) );


    //arrowModelMat0 = glm::translate( arrowModelMat0, glm::vec3( -0.5f, 0.0f, 1.0f ) );


//    const glm::vec4 eye = glm::vec4(0.0, -m_arenaSize + m_ballHeight, 3.0, 1.0);
//    const glm::vec4 look = glm::vec4(0.0, 0.0, -1.0, 0.0);
//    const glm::vec4 up = glm::vec4(0.0, 1.0, 0.0, 0.0);
//    m_camera.orientLook(eye, look, up);

//    m_camera.rotateV(-m_angleX);
//    m_camera.rotateU(-m_angleY);
//    m_camera.translate(glm::vec4(-m_xDiff, 0.0f, -m_zDiff, 1.0f));


    //arrowModelMat0 = m_camera.getRotation(eye, up, m_camera.degree2Radians((m_firedAngleX)));
    //glm::vec4 new_eye = eye + glm::vec4()
    //arrowModelMat0 = glm::translate(arrowModelMat0, glm::vec3(-m_firedXDiff, 0.0, -m_firedZDiff));
    // Transform to get to camera coordinates to render the arrow.
    glm::mat4 arrowModelMat0 = glm::mat4( 1.0f );


    arrowModelMat0 = glm::translate(arrowModelMat0, m_arrowPos);
    glm::vec4 new_eye = eye + glm::vec4(-m_firedXDiff, 0.0, -m_firedZDiff, 0.0);
    glm::mat4 rotateX = m_camera.getRotation(new_eye, up, m_camera.degree2Radians(-m_firedAngleX));
    arrowModelMat0 =  rotateX * arrowModelMat0;
    glm::vec4 r_axis = rotateX * glm::vec4(1.0, 0.0, 0.0, 0.0);
    arrowModelMat0 = m_camera.getRotation(new_eye, r_axis, m_camera.degree2Radians(-m_firedAngleY)) * arrowModelMat0;
    arrowModelMat0 = arrowModelMat0 * m_camera.getScale(glm::vec4(0.5));

    glm::vec4 new_pos = arrowModelMat0 * glm::vec4(0.0, 0.0, 0.0, 1.0);

    m_arrowPos = glm::vec3(new_pos);

    if ( !m_fired )
        arrow_vel = glm::normalize(glm::transpose(glm::inverse(glm::mat3x3(arrowModelMat0))) *
            glm::vec3(0.0, 0.0, -1));
    else
    {
//        m_arrowPos += time * arrow_vel;
        //m_arrowPos += 1 * arrow_vel;
        //std::cout << arrow_vel.x << ' ' << arrow_vel.y << ' ' << arrow_vel.z << std::endl;
        //arrowModelMat0 = glm::translate(arrowModelMat0, time * arrow_vel);
        glm::vec3 cur_pos = glm::vec3(new_pos) + arrow_vel * time;
        arrowModelMat0 = glm::translate(glm::mat4(1.0f), cur_pos);
        arrowModelMat0 = glm::scale(arrowModelMat0, glm::vec3(0.5));
//        arrowModelMat0 = glm::translate(glm::mat4(1.0f), m_arrowPos);
    }



    // Look for a hit, and if we find one, stop the arrow.
    if(m_canCollide && ( (float )glm::length( ( m_arrowPos - m_targetPos ) ) < m_arrowRadius + m_targetRadius )
            && m_timer.isActive())
    {
        m_scoreLabel->setText("Score: " + QString::number(++m_score));
//        m_testLabel->setText("chouchou");
        m_timer.stop();
    }

    //if ( m_fired )
      //  arrowModelMat0 = glm::translate(arrowModelMat0, m_arrowPos);

//    printMatrix(arrowModelMat0);
    //arrowModelMat0 = glm::scale(arrowModelMat0, glm::vec3(0.3));
//    printMatrix(glm::scale(glm::mat4x4(1.0), glm::vec3(0.075)));
//    std::cout<<"-------"<<std::endl;

    //std::cout << m_camera.degree2Radians((m_firedAngleX)) << std::endl;
   // printMatrix(arrowModelMat0);
//    arrowModelMat0 = m_camera.getRotation(3, up, -m_angleX);

//    if(!m_fired)
//    {
//        arrowModelMat0 = glm::rotate( arrowModelMat0, 0.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
//    }
    // Move and rotate to make the arrow face straight.
//    else
//    {
//        arrowModelMat0 = glm::translate(arrowModelMat0,
//                glm::vec3( qMin( 0.5f * time, 0.5f ), 0.0f, qMax( -0.7f, -1.0f * time) ) );
//        arrowModelMat0 = glm::rotate( arrowModelMat0,
//                qMax( 15.0f - ( time * 30 ), 0.5f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
//    }

//    glm::mat4 arrowModelMat1 = arrowModelMat0;

    // Arrowhead
    glm::vec3 Ka = glm::vec3( 1.0f, 0.0f, 0.0f );
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
    //arrowModelMat0 = glm::scale( arrowModelMat0, glm::vec3( 0.075f) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowModelMat0[ 0 ][ 0 ] );
    m_sphere->draw();

//    // Shaft
//    Ka = glm::vec3( 0.37f, 0.15f, 0.02f );
//    m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
//    arrowModelMat1 = glm::translate( arrowModelMat0, glm::vec3( 0.0f, 0.0f, -0.48f ) );
//    arrowModelMat1 = glm::scale( arrowModelMat1, glm::vec3( 0.075f, 0.075f, 0.48f ) );
//    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowModelMat1[ 0 ][ 0 ] );
//    m_sphere->draw();

//    // Back bit
//    Ka = glm::vec3( 0.0f, 0.7f, 0.0f );
//    m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
//    arrowModelMat1 = glm::translate( arrowModelMat0, glm::vec3( 0.0f, 0.0f, -0.96f ) );
//    arrowModelMat1 = glm::scale( arrowModelMat1, glm::vec3( 0.075f ) );
//    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowModelMat1[0][0] );
//    m_sphere->draw();
}


/**
 * Renders the bow object.
 */
void GLWidget::renderBow()
{
    glm::mat4 modelMat0 = glm::mat4( 1.0f );

    modelMat0 = glm::translate( modelMat0, glm::vec3( -m_xDiff, 0, -m_zDiff ) );
    modelMat0 = glm::rotate(modelMat0, m_angleY, glm::vec3(cos(M_PI*m_angleX/180), 0.0f, sin(M_PI*m_angleX/180)));
    modelMat0 = glm::rotate(modelMat0,-m_angleX, glm::vec3(0,1,0));

    modelMat0 = glm::rotate( modelMat0, 15.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    modelMat0 = glm::translate( modelMat0, glm::vec3( -0.8f, 0.5f, -2.5f ) );
    modelMat0 = glm::scale( modelMat0, glm::vec3( 2.5f, 2.5f, 2.5f ) );

    modelMat0 = glm::translate( modelMat0, glm::vec3( 0.0f, 0.0f, 1.0f ) );

    // String
    glm::vec3 Ka = glm::vec3( 0.37f, 0.15f, 0.02f);
    glm::mat4 modelMat1 = glm::mat4( 1.0f );

    // Bow
    Ka = glm::vec3( 1.0f, 0.0f, 0.0f );
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
    modelMat1 = glm::translate( modelMat0, glm::vec3( 0.0f, -0.225f, 0.21f ) );
    modelMat1 = glm::scale( modelMat1, glm::vec3( .005f, 0.15f, .005f ) );
    modelMat1 = glm::rotate( modelMat1, 90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat1[0][0] );
    m_sphere->draw();

    modelMat1 = glm::translate( modelMat0, glm::vec3( 0.0f, 0.035f, 0.005f ) );
    modelMat1 = glm::rotate( modelMat1, 30.0f, glm::vec3( 1.0f, .0f, 0.0f ) );
    modelMat1 = glm::scale( modelMat1, glm::vec3( 0.005f, 0.005f, .25f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat1[0][0] );
    m_sphere->draw();

    modelMat1 = glm::translate( modelMat0, glm::vec3( 0.0f, -0.4825f, 0.005f ) );
    modelMat1 = glm::rotate( modelMat1, -30.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    modelMat1 = glm::scale( modelMat1, glm::vec3( .005f, 0.005f, .25f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat1[0][0] );
    m_sphere->draw();
}


/**
 * Renders the six walls of the room using quads.
 */
void GLWidget::renderRoom()
{
    //render the walls, floor and ceiling of our playing field
    glm::vec3 Ka = glm::vec3( 0.0f, 0.7f, 0.93f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );

//    // Ceiling
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 5.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, 90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0] );
    m_quad->draw();

//    // Back
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, 5.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, 180.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0] );
    m_quad->draw();

//    // Right
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 5.0f, 0.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, -90.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    m_quad->draw();

//    // Left
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( -5.0f, 0.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, 90.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    m_quad->draw();

//    // Front
    glActiveTexture(GL_TEXTURE0); // Set the active texture to texture 0.
    m_shader.setUniform("textureSampler", Shader::INT, 0);

    Ka = glm::vec3(0.9f, 0.74f, 0.2f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, -5.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    m_quad->draw();
    glBindTexture(GL_TEXTURE_2D, 0);

//    // Ground
    Ka = glm::vec3(0.3f, 0.74f, 0.2f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, -90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    m_quad->draw();
}


/**
 * Called when the screen gets resized.
 * The camera is updated when the screen resizes because the aspect ratio may change.
 */
void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    updateCamera();
}


/**
 * Update the camera's specifications.
 * It gets called in resizeGL which get called automatically on intialization
 * and whenever the window is resized.
 */
void GLWidget::updateCamera()
{
    float w = width();
    float h = height();
//    float aspectRatio = 1.0f * w / h;
//    m_projectionMatrix = glm::mat4(1.0);
//    m_projectionMatrix = glm::perspective( m_camera.fovy, aspectRatio, m_camera.near, m_camera.far );

    m_projectionMatrix = m_camera.getProjectionMatrix();
    m_shader.setUniform( "P_Matrix", Shader::MAT4, &m_projectionMatrix[0][0] );

//    const glm::vec4 eye = glm::vec4(0.0, -m_arenaSize + m_ballHeight, 3.0, 1.0);
//    const glm::vec4 look = glm::vec4(0.0, 0.0, -1.0, 0.0);
//    const glm::vec4 up = glm::vec4(0.0, 1.0, 0.0, 0.0);
    m_camera.orientLook(eye, look, up);


    m_camera.rotateV(-m_angleX);
    m_camera.rotateU(-m_angleY);
    m_camera.translate(glm::vec4(-m_xDiff, 0.0f, -m_zDiff, 1.0f));

    m_viewMatrix = m_camera.getViewMatrix();

//    m_viewMatrix = glm::lookAt( m_camera.eye,  m_camera.center, m_camera.up );
//    m_viewMatrix = glm::rotate( m_viewMatrix,  m_angleX, glm::vec3( 0.0f, 1.0f, 0.0f) );
////    std::cout<<m_angleY<<std::endl;
    //m_viewMatrix = glm::rotate( m_viewMatrix, m_angleY, glm::vec3( cos(M_PI*m_angleX/180), 0.0f, sin(M_PI*m_angleX/180) ) );

//    m_viewMatrix = glm::translate( m_viewMatrix, glm::vec3( m_xDiff, 0.0f, m_zDiff) );

//    std::cout << m_xDiff << ' ' << m_zDiff << std::endl;

    m_shader.setUniform( "V_Matrix", Shader::MAT4, &m_viewMatrix[0][0] );

//    std::cout << m_camera.center.x << ' ' << m_camera.center.y << ' ' << m_camera.center.z << std::endl;
}


/**
 * Handles key press events to allow for movement
 */
void GLWidget::keyPressEvent ( QKeyEvent * event )
{
    //we adjust how we move by what angle we're currently facing
    double cx = cos(m_angleX * M_PI/180);
    double sx = sin(m_angleX * M_PI/180);
    if(event->key() == Qt::Key_W)
    {
        m_zDiff += 0.25f * cx;
        m_xDiff -= 0.25f * sx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_S)
    {
        m_zDiff -= 0.25f * cx;
        m_xDiff += 0.25f * sx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_D)
    {
        m_zDiff -= 0.25f * sx;
        m_xDiff -= 0.25f * cx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_A)
    {
        m_zDiff += 0.25f * sx;
        m_xDiff += 0.25f * cx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_Escape)
    {
        m_firstPersonMode = false;
        m_originalMouseX = -1;
        m_originalMouseY = -1;
    }
    if(event->key() == Qt::Key_Space)
    {
//        std::cout << "space press!" << std::endl;
        m_power++;
        m_powerSlot->setValue(m_power);
        Basketball *cur_b = m_basketballList[m_basketballList.size() - 1];
        cur_b->setPower(m_power);
        update();
    }
}


void GLWidget::keyReleaseEvent ( QKeyEvent * event ){
//    if ( !event->isAutoRepeat() && event->key() == Qt::Key_Space){
//        std::cout << "space release!" << std::endl;
//        m_powerSlot->setValue(m_power);
//        Basketball *cur_b = m_basketballList[m_basketballList.size() - 1];
//        cur_b->fireBasketball();
//        initBasketball();
//        m_power = 0;
//        update();
//    }


//    if (event->key() == Qt::Key_Space)
//    {
//        if(event->isAutoRepeat())
//            std::cout << "autorepeat!" << std::endl;
////        else
////            std::cout << "release!" << std::endl;
//    }

}


/**
 * Handles mouse movement events for camera rotation
 */
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_firstPersonMode) {
        if(m_originalMouseX < 0 && m_originalMouseY < 0)
        {
            m_originalMouseX = event->globalX() - event->x() + this->width()/2;
            m_originalMouseY = event->globalY() - event->y() + this->height()/2;
            QCursor::setPos(m_originalMouseX, m_originalMouseY);
        }
        else
        {
            float x = event->globalX();
            float y = event->globalY();
            rotateCamera(x - m_originalMouseX, y-m_originalMouseY);
            update();
            QCursor::setPos(m_originalMouseX, m_originalMouseY);
        }
        update();
    }
}


/**
 * Handles click events. Enters first person mode if the user isn't in first person mode,
 * shoots an arrow if the user has an arrow to shoot and picks up an arrow if the user has
 * none.
 */
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(!m_firstPersonMode){
        m_firstPersonMode = true;
        m_originalMouseX = event->globalX() - event->x() + this->width()/2;
        m_originalMouseY = event->globalY() - event->y() + this->height()/2;
        QCursor::setPos(m_originalMouseX, m_originalMouseY);
        m_timer.start(1000.0f / m_fps);
    }
    else {
        m_originalMouseX = event->globalX();
        m_originalMouseY = event->globalY();
//        if(m_increment == 0.0f && !m_timer.isActive())
//        {
//            //start the timer if the increment is 0
//            m_timer.start(1000.0f / m_fps);
//            m_fired = true;
//        }
//        else
//        {
//            //reset the timer
//            m_increment = 0.0f;
//            m_fired = false;
//            m_timer.stop();
//        }
        Basketball *cur_b = m_basketballList[m_basketballList.size() - 1];
        cur_b->fireBasketball();
        initBasketball();
        m_power = 1;
        m_powerSlot->setValue(m_power);
        update();
    }

}


//        std::cout << "space release!" << std::endl;
//        m_powerSlot->setValue(m_power);
//        Basketball *cur_b = m_basketballList[m_basketballList.size() - 1];
//        cur_b->fireBasketball();
//        initBasketball();
//        m_power = 0;
//        update();


/**
 * Modifies the angle that the user is looking via deltaX and deltaY.
 */
void GLWidget::rotateCamera(float deltaX, float deltaY)
{
    m_angleX +=  deltaX * 0.025;
    m_angleY +=  deltaY * 0.025;
    m_angleY = qMax(-90 + 0.001, qMin(90 - 0.001, (double)m_angleY));
//    std::cout<<m_angleX<<" "<<m_angleY<<std::endl;
    updateCamera();
}


/**
 * Called when the settings are updated through the UI.
 * This is already filled in for you.
 */
void GLWidget::updateSettings()
{
    update();
}


/**
 * Allows the ui to set the label to be modified to update score
 */
void GLWidget::setLabel(QLabel* label)
{
    m_scoreLabel = label;
}

void GLWidget::setProgressBar(QProgressBar *pBar)
{
    m_powerSlot = pBar;
    m_powerSlot->setValue(m_power);
}


/**
 * Sets the position of the target, and notifies the system that we are ready to attempt collisions
 */
void GLWidget::setTargetPosition(glm::vec3 pos)
{
    m_canCollide = true;
    m_targetPos = pos;
}


/**
 * Specifies to Qt what to do when the widget needs to be updated.
 * We only want to repaint the onscreen objects.
 */
void GLWidget::tick()
{
//    m_increment++;
    update();
//    if(m_increment > m_fps )
//    {
//        //reset the timer and set fired to false
//        m_timer.stop();
//        m_increment = 0.0f;
//        m_fired = false;
//    }
//    std::cout<<m_increment<<std::endl;
}
