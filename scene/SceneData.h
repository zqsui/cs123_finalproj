#ifndef SCENEDATA_H
#define SCENEDATA_H
#include <GL/glew.h>
#include <GL/gl.h>
#include "glm/glm/glm.hpp"
#include <vector>

enum PrimitiveType {
    PRIMITIVE_CUBE,
    PRIMITIVE_CONE,
    PRIMITIVE_CYLINDER,
    PRIMITIVE_TORUS,
    PRIMITIVE_SPHERE,
    PRIMITIVE_QUAD
};

enum WallType {
   WALL_BRICK,
   WALL_GROUND,
   WALL_SKY
};


struct Plane{
    float a, b, c, d;    
    float width;
    float height;
    glm::vec3 width_vec;
    glm::vec3 height_vec;
    glm::vec3 normal;
    glm::vec3 centroid;
    glm::mat4 modelMat;
};


struct Wall{
    glm::vec3 Ka;
    glm::mat4 modelMat;
//    glm::vec3 translation;
//    glm::vec3 scaling;
//    glm::vec3 rotation;
    float mass;
    glm::vec3 vel;
    glm::vec3 normal;
    Plane plane;
    int wallType;

};

struct Hoop{
    glm::vec3 Ka;
    glm::mat4 modelMat;
    float mass;
    glm::vec3 vel;
    std::vector<Plane> plane;
};

struct BasketballStand{
    glm::vec3 Ka;
    glm::mat4 modelMat;
    float mass;
    glm::vec3 vel;
    glm::vec3 normal;
    Plane plane;
};

struct BackBoard{
    glm::vec3 Ka;
    glm::mat4 modelMat;
    float mass;
    glm::vec3 vel;
    glm::vec3 normal;
    Plane plane;    
};

struct HoopBoard
{
    glm::vec3 Ka;
    glm::mat4 modelMat;
    float mass;
    glm::vec3 vel;
    int object_type;
    Plane plane;
};




//glm::vec3 Ka = glm::vec3( 0.0f, 0.7f, 0.93f);
//m_shader.setUniform( "Ka", Shader::VEC3, &Ka[0] );

////    // Ceiling
//glm::mat4 modelMat = glm::mat4(1.0f);
//modelMat = glm::translate( modelMat, glm::vec3( 0.0f, 5.0f, 0.0f ) );
//modelMat = glm::scale( modelMat, glm::vec3( 5.0f ) );
//modelMat = glm::rotate(modelMat, 90.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
//m_shader.setUniform( "M_Matrix", Shader::MAT4, &modelMat[0][0] );
//m_quad->draw();





//#include "CS123Common.h"
//#include <vector>
//#include <string>

//// Enumeration for light types.
//enum LightType {
//    LIGHT_POINT, LIGHT_DIRECTIONAL, LIGHT_SPOT, LIGHT_AREA
//};

//// Enumeration for types of primitives that can be stored in a scene file.
//enum PrimitiveType {
//    PRIMITIVE_CUBE,
//    PRIMITIVE_CONE,
//    PRIMITIVE_CYLINDER,
//    PRIMITIVE_TORUS,
//    PRIMITIVE_SPHERE,
//    PRIMITIVE_MESH
//};

//// Enumeration for types of transformations that can be applied to objects, lights, and cameras.
//enum TransformationType {
//   TRANSFORMATION_TRANSLATE, TRANSFORMATION_SCALE, TRANSFORMATION_ROTATE, TRANSFORMATION_MATRIX
//};

//// Struct to store a RGBA color in floats [0,1]
//struct CS123SceneColor
//{
//    union {
//        struct {
//           float r;
//           float g;
//           float b;
//           float a;
//        };
//        float channels[4]; // points to the same four floats above...
//    };

//   // @TODO: [OPTIONAL] You can implement some operators here for color arithmetic.

//};

//// Scene global color coefficients
//struct CS123SceneGlobalData
//{
//   float ka;  // global ambient coefficient
//   float kd;  // global diffuse coefficient
//   float ks;  // global specular coefficient
//   float kt;  // global transparency coefficient
//};

//// Data for a single light
//struct CS123SceneLightData
//{
//   int id;
//   LightType type;

//   CS123SceneColor color;
//   glm::vec3 function;  // Attenuation function

//   glm::vec4 pos;       // Not applicable to directional lights
//   glm::vec4 dir;       // Not applicable to point lights

//   float radius;        // Only applicable to spot lights
//   float penumbra;      // Only applicable to spot lights
//   float angle;         // Only applicable to spot lights

//   float width, height; // Only applicable to area lights
//};

//// Data for scene camera
//struct CS123SceneCameraData
//{
//   glm::vec4 pos;
//   glm::vec4 look;
//   glm::vec4 up;

//   float heightAngle;
//   float aspectRatio;

//   float aperture;      // Only applicable for depth of field
//   float focalLength;   // Only applicable for depth of field
//};

//// Data for file maps (ie: texture maps)
//struct CS123SceneFileMap
//{
//    CS123SceneFileMap() : texid(0) {}
//   bool isUsed;
//   std::string filename;
//   float repeatU;
//   float repeatV;
//   GLuint texid;
//};

//// Data for scene materials
//struct CS123SceneMaterial
//{
//   // This field specifies the diffuse color of the object. This is the color you need to use for
//   // the object in sceneview. You can get away with ignoring the other color values until
//   // intersect and ray.
//   CS123SceneColor cDiffuse;

//   CS123SceneColor cAmbient;
//   CS123SceneColor cReflective;
//   CS123SceneColor cSpecular;
//   CS123SceneColor cTransparent;
//   CS123SceneColor cEmissive;

//   CS123SceneFileMap* textureMap;
//   float blend;

//   CS123SceneFileMap* bumpMap;

//   float shininess;

//   float ior; // index of refraction
//};

//// Data for a single primitive.
//struct CS123ScenePrimitive
//{
//   PrimitiveType type;
//   std::string meshfile;     // Only applicable to meshes
//   CS123SceneMaterial material;
//};

//// Data for transforming a scene object. Aside from the TransformationType, the remaining of the
//// data in the struct is mutually exclusive.
//struct CS123SceneTransformation
//{
//    // Whether the transformation is a rotation, translation, scale, or custom matrix.
//    TransformationType type;

//    glm::vec3 translate; // The translation vector. Only valid if transformation is a translation.
//    glm::vec3 scale;     // The scale vector. Only valid if transformation is a scale.
//    glm::vec3 rotate;    // The axis of rotation. Only valid if the transformation is a rotation.
//    float angle;         // The rotation angle in RADIANS. Only valid if transformation is a
//                         // rotation.

//    glm::mat4x4 matrix;  // The matrix for the transformation. Only valid if the transformation is
//                         // a custom matrix.
//};

//// Structure for non-primitive scene objects
//struct CS123SceneNode
//{
//   // Transformation at this node
//   std::vector<CS123SceneTransformation*> transformations;

//   // Primitives at this node
//   std::vector<CS123ScenePrimitive*> primitives;

//   // Children of this node
//   std::vector<CS123SceneNode*> children;
//};

//#endif


#endif // SCENEDATA_H
