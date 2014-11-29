#include "glwidget.h"
#include "Settings.h"
#include "Shader.h"
#include <iostream>

#include <GL/glew.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/string_cast.hpp"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent), m_timer(this), m_fps(60.0f), m_increment(0), m_angleX(0.0f),
      m_angleY(0.0f), m_xDiff(0.0f), m_zDiff(0.0f), m_arrowRadius(0.1), m_targetRadius(0.5),
      m_score(0), m_canCollide(false)
{

    // Set up the camera
    m_camera.eye.x = 0.0f, m_camera.eye.y = 0.0f, m_camera.eye.z = -1.0f;
    m_camera.center.x = 0.0f, m_camera.center.y = 0.0f, m_camera.center.z = 0.0f;
    m_camera.up.x = 0.0f, m_camera.up.y = 1.0f, m_camera.up.z = 0.0f;
    m_camera.fovy = 45.0f, m_camera.near = 0.95f, m_camera.far = 1000.0f;

    // Set up 60 FPS draw loop
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));

    this->setMouseTracking(true);
    m_originalMouseX = -1;
    m_originalMouseY = -1;

    m_arrowPos = glm::vec3(0,0,0);
    m_targetPos = m_arrowPos;
}


GLWidget::~GLWidget()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
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
    m_sphere = new Sphere( m_shader.attrib("in_Position"), m_shader.attrib("in_Normal") );
    initTarget();
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
    targetModelMat =glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 3.0));
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &targetModelMat[ 0 ][ 0 ]);
    setTargetPosition(glm::vec3(0, 0, 3.0));
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

    // Set lighting properties.
    glm::vec3 La = glm::vec3( 0.2f, 0.2f, 0.2f );
    m_shader.setUniform( "La", Shader::VEC3, &La );

    glm::vec3 Lpos = glm::vec3( 1.0f, 1.0f, 1.0f );
    m_shader.setUniform( "Lpos", Shader::VEC3, &Lpos );
    glm::vec3 Ld = glm::vec3( 1.0f, 1.0f, 1.0f );
    m_shader.setUniform( "Ld", Shader::VEC3, &Ld );
    updateSettings();
    updateCamera();
    initShapes();
}


/**
 * The main drawing method which will be called 30 frames per second.
 */
void GLWidget::paintGL()
{
    // If we haven't fired yet, update the angles so that the arrow's angles and position to
    // match the camera's.
    if(!m_fired)
    {
        m_firedAngleX = m_angleX;
        m_firedAngleY = m_angleY;
        m_firedXDiff = m_xDiff;
        m_firedZDiff = m_zDiff;
    }

    // Clear the color and depth buffers to the current glClearColor
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    renderTarget();

    renderBow();

    renderArrow();

    renderRoom();

    //Render intersection spheres
    if(m_canCollide && settings.showIntersectSpheres)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::vec3 Ka = glm::vec3( 0.5f );
        m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
        renderTargetSphere();

        renderArrowSphere();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    m_arrowPos =  glm::vec3( -m_firedXDiff, 0.0f, -m_firedZDiff );
    // Set the velocity to reflect the rotation transforms we do to render the arrow.
    // We keep variables for all the values we need for this to simplify the velocity vector.
    double cx = cos( -m_firedAngleX * M_PI / 180.0f );
    double sx = sin( -m_firedAngleX * M_PI / 180.0f );
    double cy = cos( m_firedAngleY * M_PI / 180.0f );
    double omcy = 1.0f - cy;
    double sy = sin( m_firedAngleY * M_PI / 180.0f );

    double cmx = cos( M_PI * m_firedAngleX / 180.0f );
    double smx = sin( M_PI * m_firedAngleX / 180.0f );

    // Calculates through the rotates done to get an accurate velocity vector.
    glm::vec3 vel = glm::vec3( ( ( sx * ( ( cmx * cmx * omcy ) + cy ) ) + ( cx * cmx * smx * omcy ) ),
                               ( ( sx * smx * sy) - ( cx * cmx * sy ) ),
                               ( ( sx * cmx * smx * omcy) + ( cx * ( ( smx * smx * omcy ) + cy ) ) ) );

    // Move the arrow's position based on velocity and time.
    m_arrowPos += time * vel;

    // Look for a hit, and if we find one, stop the arrow.
    if(m_canCollide && ( (float )glm::length( ( m_arrowPos - m_targetPos ) ) < m_arrowRadius + m_targetRadius )
            && m_timer.isActive())
    {
        m_scoreLabel->setText("Score: " + QString::number(++m_score));
        m_timer.stop();
    }

    // Transform to get to camera coordinates to render the arrow.
    glm::mat4 arrowModelMat0 = glm::mat4( 1.0f );

    arrowModelMat0 = glm::translate( arrowModelMat0, m_arrowPos );
    arrowModelMat0 = glm::rotate( arrowModelMat0,  m_firedAngleY, glm::vec3( cmx, 0.0f, smx ) );
    arrowModelMat0 = glm::rotate( arrowModelMat0, -m_firedAngleX, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    arrowModelMat0 = glm::translate( arrowModelMat0, glm::vec3( -0.5f, 0.0f, 1.0f ) );

    if(!m_fired)
    {
        arrowModelMat0 = glm::rotate( arrowModelMat0, 30.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    }
    // Move and rotate to make the arrow face straight.
    else
    {
        arrowModelMat0 = glm::translate(arrowModelMat0,
                glm::vec3( qMin( 0.5f * time, 0.5f ), 0.0f, qMax( -0.7f, -1.0f * time) ) );
        arrowModelMat0 = glm::rotate( arrowModelMat0,
                qMax( 15.0f - ( time * 30 ), 0.5f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
    }

    glm::mat4 arrowModelMat1 = arrowModelMat0;

    // Arrowhead
    glm::vec3 Ka = glm::vec3( 0.0f );
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
    arrowModelMat1 = glm::scale( arrowModelMat0, glm::vec3( 0.075f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowModelMat1[ 0 ][ 0 ] );
    m_sphere->draw();

    // Shaft
    Ka = glm::vec3( 0.37f, 0.15f, 0.02f );
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
    arrowModelMat1 = glm::translate( arrowModelMat0, glm::vec3( 0.0f, 0.0f, -0.48f ) );
    arrowModelMat1 = glm::scale( arrowModelMat1, glm::vec3( 0.075f, 0.075f, 0.48f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowModelMat1[ 0 ][ 0 ] );
    m_sphere->draw();

    // Back bit
    Ka = glm::vec3( 0.0f, 0.7f, 0.0f );
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka );
    arrowModelMat1 = glm::translate( arrowModelMat0, glm::vec3( 0.0f, 0.0f, -0.96f ) );
    arrowModelMat1 = glm::scale( arrowModelMat1, glm::vec3( 0.075f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &arrowModelMat1[0][0] );
    m_sphere->draw();
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

    // Ceiling
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 5.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, 90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0] );
    m_quad->draw();

    // Back
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, -5.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0] );
    m_quad->draw();

    // Right
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( -5.0f, 0.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, 90.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    m_quad->draw();

    // Left
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 5.0f, 0.0f, 0.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, -90.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    m_quad->draw();

    // Front
    Ka = glm::vec3(0.9f, 0.74f, 0.2f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 0.0f, 5.0f ) );
    modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
    modelMat = glm::rotate(modelMat, 180.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0]);
    m_quad->draw();

    // Ground
    Ka = glm::vec3(0.3f, 0.74f, 0.2f);
    m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate( modelMat, glm::vec3( 0.0f, -1.0f, 0.0f ) );
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
    float aspectRatio = 1.0f * w / h;
    m_projectionMatrix = glm::mat4(1.0);
    m_projectionMatrix = glm::perspective( m_camera.fovy, aspectRatio, m_camera.near, m_camera.far );
    m_shader.setUniform( "P_Matrix", Shader::MAT4, &m_projectionMatrix[0][0] );

    m_viewMatrix = glm::lookAt( m_camera.eye,  m_camera.center, m_camera.up );
    m_viewMatrix = glm::rotate( m_viewMatrix,  m_angleX, glm::vec3( 0.0f, 1.0f, 0.0f) );
    m_viewMatrix = glm::rotate( m_viewMatrix, -m_angleY, glm::vec3( cos(M_PI*m_angleX/180), 0.0f, sin(M_PI*m_angleX/180) ) );
    m_viewMatrix = glm::translate( m_viewMatrix, glm::vec3( m_xDiff, 0.0f, m_zDiff) );

    m_shader.setUniform( "V_Matrix", Shader::MAT4, &m_viewMatrix[0][0] );
}


/**
 * Handles key press events to allow for movement
 */
void GLWidget::keyPressEvent ( QKeyEvent * event )
{
    //we adjust how we move by what angle we're currently facing
    double cx = cos(-m_angleX * M_PI/180);
    double sx = sin(-m_angleX * M_PI/180);
    if(event->key() == Qt::Key_W)
    {
        m_zDiff -= 0.025f * cx;
        m_xDiff -= 0.025f * sx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_S)
    {
        m_zDiff += 0.025f * cx;
        m_xDiff += 0.025f * sx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_D)
    {
        m_zDiff += 0.025f * -sx;
        m_xDiff += 0.025f * cx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_A)
    {
        m_zDiff -= 0.025f * -sx;
        m_xDiff -= 0.025f * cx;
        this->updateCamera();
        this->update();
    }
    else if(event->key() == Qt::Key_Escape)
    {
        m_firstPersonMode = false;
        m_originalMouseX = -1;
        m_originalMouseY = -1;
    }
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
    }
    else {
        m_originalMouseX = event->globalX();
        m_originalMouseY = event->globalY();
        if(m_increment == 0.0f && !m_timer.isActive())
        {
            //start the timer if the increment is 0
            m_timer.start(1000.0f / m_fps);
            m_fired = true;
        }
        else
        {
            //reset the timer
            m_increment = 0.0f;
            m_fired = false;
            m_timer.stop();
        }
        update();
    }

}


/**
 * Modifies the angle that the user is looking via deltaX and deltaY.
 */
void GLWidget::rotateCamera(float deltaX, float deltaY)
{
    m_angleX +=  deltaX * 0.025;
    m_angleY +=  deltaY * 0.025;
    m_angleY = qMax(-90 + 0.001, qMin(90 - 0.001, (double)m_angleY));
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
    m_increment++;
    update();
    if(m_increment/(float) m_fps > 1.0f)
    {
        //reset the timer and set fired to false
        m_timer.stop();
        m_increment = 0.0f;
        m_fired = false;
    }
}
