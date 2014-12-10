//#include "Sphere.h"
//#include <iostream>

//#define NUM_TRIS 200

//Sphere::Sphere()
//{
//    m_isInitialized = false;
//}

//Sphere::Sphere(const GLuint vertexLocation, const GLuint normalLocation){
//    init(vertexLocation, normalLocation);
//}

//Sphere::~Sphere()
//{
//    glDeleteVertexArrays(1, &m_vaoID);
//    glDeleteBuffers(1, &m_vbo);
//}

//void Sphere::init(const GLuint vertexLocation, const GLuint normalLocation){
//    m_isInitialized = true;

//    GLfloat vertexBufferData[] = {
//        0.154508, 0.475528, 0,
//        -2.18557e-08, 0.5, -0,
//        -1.76816e-08, 0.5, -1.28465e-08,
//        0.125, 0.475528, 0.0908178,
//        0.154508, 0.475528, 0,
//        -1.76816e-08, 0.5, -1.28465e-08,
//        0.125, 0.475528, 0.0908178,
//        -1.76816e-08, 0.5, -1.28465e-08,
//        -6.75378e-09, 0.5, -2.0786e-08,
//        0.0477457, 0.475528, 0.146946,
//        0.125, 0.475528, 0.0908178,
//        -6.75378e-09, 0.5, -2.0786e-08,
//        0.0477457, 0.475528, 0.146946,
//        -6.75378e-09, 0.5, -2.0786e-08,
//        6.75378e-09, 0.5, -2.0786e-08,
//        -0.0477458, 0.475528, 0.146946,
//        0.0477457, 0.475528, 0.146946,
//        6.75378e-09, 0.5, -2.0786e-08,
//        -0.0477458, 0.475528, 0.146946,
//        6.75378e-09, 0.5, -2.0786e-08,
//        1.76816e-08, 0.5, -1.28465e-08,
//        -0.125, 0.475528, 0.0908178,
//        -0.0477458, 0.475528, 0.146946,
//        1.76816e-08, 0.5, -1.28465e-08,
//        -0.125, 0.475528, 0.0908178,
//        1.76816e-08, 0.5, -1.28465e-08,
//        2.18557e-08, 0.5, 1.91069e-15,
//        -0.154508, 0.475528, -1.35076e-08,
//        -0.125, 0.475528, 0.0908178,
//        2.18557e-08, 0.5, 1.91069e-15,
//        -0.154508, 0.475528, -1.35076e-08,
//        2.18557e-08, 0.5, 1.91069e-15,
//        1.76816e-08, 0.5, 1.28465e-08,
//        -0.125, 0.475528, -0.0908178,
//        -0.154508, 0.475528, -1.35076e-08,
//        1.76816e-08, 0.5, 1.28465e-08,
//        -0.125, 0.475528, -0.0908178,
//        1.76816e-08, 0.5, 1.28465e-08,
//        6.75378e-09, 0.5, 2.0786e-08,
//        -0.0477458, 0.475528, -0.146946,
//        -0.125, 0.475528, -0.0908178,
//        6.75378e-09, 0.5, 2.0786e-08,
//        -0.0477458, 0.475528, -0.146946,
//        6.75378e-09, 0.5, 2.0786e-08,
//        -6.75378e-09, 0.5, 2.0786e-08,
//        0.0477458, 0.475528, -0.146946,
//        -0.0477458, 0.475528, -0.146946,
//        -6.75378e-09, 0.5, 2.0786e-08,
//        0.0477458, 0.475528, -0.146946,
//        -6.75378e-09, 0.5, 2.0786e-08,
//        -1.76816e-08, 0.5, 1.28465e-08,
//        0.125, 0.475528, -0.0908178,
//        0.0477458, 0.475528, -0.146946,
//        -1.76816e-08, 0.5, 1.28465e-08,
//        0.125, 0.475528, -0.0908178,
//        -1.76816e-08, 0.5, 1.28465e-08,
//        -2.18557e-08, 0.5, -3.82137e-15,
//        0.154508, 0.475528, 2.70151e-08,
//        0.125, 0.475528, -0.0908178,
//        -2.18557e-08, 0.5, -3.82137e-15,
//        0.293893, 0.404508, 0,
//        0.154508, 0.475528, 0,
//        0.125, 0.475528, 0.0908178,
//        0.237764, 0.404508, 0.172746,
//        0.293893, 0.404508, 0,
//        0.125, 0.475528, 0.0908178,
//        0.237764, 0.404508, 0.172746,
//        0.125, 0.475528, 0.0908178,
//        0.0477457, 0.475528, 0.146946,
//        0.0908178, 0.404508, 0.279509,
//        0.237764, 0.404508, 0.172746,
//        0.0477457, 0.475528, 0.146946,
//        0.0908178, 0.404508, 0.279509,
//        0.0477457, 0.475528, 0.146946,
//        -0.0477458, 0.475528, 0.146946,
//        -0.0908178, 0.404508, 0.279509,
//        0.0908178, 0.404508, 0.279509,
//        -0.0477458, 0.475528, 0.146946,
//        -0.0908178, 0.404508, 0.279509,
//        -0.0477458, 0.475528, 0.146946,
//        -0.125, 0.475528, 0.0908178,
//        -0.237764, 0.404508, 0.172746,
//        -0.0908178, 0.404508, 0.279509,
//        -0.125, 0.475528, 0.0908178,
//        -0.237764, 0.404508, 0.172746,
//        -0.125, 0.475528, 0.0908178,
//        -0.154508, 0.475528, -1.35076e-08,
//        -0.293893, 0.404508, -2.56929e-08,
//        -0.237764, 0.404508, 0.172746,
//        -0.154508, 0.475528, -1.35076e-08,
//        -0.293893, 0.404508, -2.56929e-08,
//        -0.154508, 0.475528, -1.35076e-08,
//        -0.125, 0.475528, -0.0908178,
//        -0.237764, 0.404508, -0.172746,
//        -0.293893, 0.404508, -2.56929e-08,
//        -0.125, 0.475528, -0.0908178,
//        -0.237764, 0.404508, -0.172746,
//        -0.125, 0.475528, -0.0908178,
//        -0.0477458, 0.475528, -0.146946,
//        -0.0908179, 0.404508, -0.279509,
//        -0.237764, 0.404508, -0.172746,
//        -0.0477458, 0.475528, -0.146946,
//        -0.0908179, 0.404508, -0.279509,
//        -0.0477458, 0.475528, -0.146946,
//        0.0477458, 0.475528, -0.146946,
//        0.0908179, 0.404508, -0.279509,
//        -0.0908179, 0.404508, -0.279509,
//        0.0477458, 0.475528, -0.146946,
//        0.0908179, 0.404508, -0.279509,
//        0.0477458, 0.475528, -0.146946,
//        0.125, 0.475528, -0.0908178,
//        0.237764, 0.404508, -0.172746,
//        0.0908179, 0.404508, -0.279509,
//        0.125, 0.475528, -0.0908178,
//        0.237764, 0.404508, -0.172746,
//        0.125, 0.475528, -0.0908178,
//        0.154508, 0.475528, 2.70151e-08,
//        0.293893, 0.404508, 5.13858e-08,
//        0.237764, 0.404508, -0.172746,
//        0.154508, 0.475528, 2.70151e-08,
//        0.404509, 0.293893, 0,
//        0.293893, 0.404508, 0,
//        0.237764, 0.404508, 0.172746,
//        0.327254, 0.293893, 0.237764,
//        0.404509, 0.293893, 0,
//        0.237764, 0.404508, 0.172746,
//        0.327254, 0.293893, 0.237764,
//        0.237764, 0.404508, 0.172746,
//        0.0908178, 0.404508, 0.279509,
//        0.125, 0.293893, 0.38471,
//        0.327254, 0.293893, 0.237764,
//        0.0908178, 0.404508, 0.279509,
//        0.125, 0.293893, 0.38471,
//        0.0908178, 0.404508, 0.279509,
//        -0.0908178, 0.404508, 0.279509,
//        -0.125, 0.293893, 0.38471,
//        0.125, 0.293893, 0.38471,
//        -0.0908178, 0.404508, 0.279509,
//        -0.125, 0.293893, 0.38471,
//        -0.0908178, 0.404508, 0.279509,
//        -0.237764, 0.404508, 0.172746,
//        -0.327254, 0.293893, 0.237764,
//        -0.125, 0.293893, 0.38471,
//        -0.237764, 0.404508, 0.172746,
//        -0.327254, 0.293893, 0.237764,
//        -0.237764, 0.404508, 0.172746,
//        -0.293893, 0.404508, -2.56929e-08,
//        -0.404509, 0.293893, -3.53633e-08,
//        -0.327254, 0.293893, 0.237764,
//        -0.293893, 0.404508, -2.56929e-08,
//        -0.404509, 0.293893, -3.53633e-08,
//        -0.293893, 0.404508, -2.56929e-08,
//        -0.237764, 0.404508, -0.172746,
//        -0.327254, 0.293893, -0.237764,
//        -0.404509, 0.293893, -3.53633e-08,
//        -0.237764, 0.404508, -0.172746,
//        -0.327254, 0.293893, -0.237764,
//        -0.237764, 0.404508, -0.172746,
//        -0.0908179, 0.404508, -0.279509,
//        -0.125, 0.293893, -0.38471,
//        -0.327254, 0.293893, -0.237764,
//        -0.0908179, 0.404508, -0.279509,
//        -0.125, 0.293893, -0.38471,
//        -0.0908179, 0.404508, -0.279509,
//        0.0908179, 0.404508, -0.279509,
//        0.125, 0.293893, -0.38471,
//        -0.125, 0.293893, -0.38471,
//        0.0908179, 0.404508, -0.279509,
//        0.125, 0.293893, -0.38471,
//        0.0908179, 0.404508, -0.279509,
//        0.237764, 0.404508, -0.172746,
//        0.327254, 0.293893, -0.237764,
//        0.125, 0.293893, -0.38471,
//        0.237764, 0.404508, -0.172746,
//        0.327254, 0.293893, -0.237764,
//        0.237764, 0.404508, -0.172746,
//        0.293893, 0.404508, 5.13858e-08,
//        0.404509, 0.293893, 7.07265e-08,
//        0.327254, 0.293893, -0.237764,
//        0.293893, 0.404508, 5.13858e-08,
//        0.475528, 0.154508, 0,
//        0.404509, 0.293893, 0,
//        0.327254, 0.293893, 0.237764,
//        0.38471, 0.154508, 0.279509,
//        0.475528, 0.154508, 0,
//        0.327254, 0.293893, 0.237764,
//        0.38471, 0.154508, 0.279509,
//        0.327254, 0.293893, 0.237764,
//        0.125, 0.293893, 0.38471,
//        0.146946, 0.154508, 0.452254,
//        0.38471, 0.154508, 0.279509,
//        0.125, 0.293893, 0.38471,
//        0.146946, 0.154508, 0.452254,
//        0.125, 0.293893, 0.38471,
//        -0.125, 0.293893, 0.38471,
//        -0.146946, 0.154508, 0.452254,
//        0.146946, 0.154508, 0.452254,
//        -0.125, 0.293893, 0.38471,
//        -0.146946, 0.154508, 0.452254,
//        -0.125, 0.293893, 0.38471,
//        -0.327254, 0.293893, 0.237764,
//        -0.38471, 0.154508, 0.279508,
//        -0.146946, 0.154508, 0.452254,
//        -0.327254, 0.293893, 0.237764,
//        -0.38471, 0.154508, 0.279508,
//        -0.327254, 0.293893, 0.237764,
//        -0.404509, 0.293893, -3.53633e-08,
//        -0.475528, 0.154508, -4.1572e-08,
//        -0.38471, 0.154508, 0.279508,
//        -0.404509, 0.293893, -3.53633e-08,
//        -0.475528, 0.154508, -4.1572e-08,
//        -0.404509, 0.293893, -3.53633e-08,
//        -0.327254, 0.293893, -0.237764,
//        -0.38471, 0.154508, -0.279509,
//        -0.475528, 0.154508, -4.1572e-08,
//        -0.327254, 0.293893, -0.237764,
//        -0.38471, 0.154508, -0.279509,
//        -0.327254, 0.293893, -0.237764,
//        -0.125, 0.293893, -0.38471,
//        -0.146946, 0.154508, -0.452254,
//        -0.38471, 0.154508, -0.279509,
//        -0.125, 0.293893, -0.38471,
//        -0.146946, 0.154508, -0.452254,
//        -0.125, 0.293893, -0.38471,
//        0.125, 0.293893, -0.38471,
//        0.146946, 0.154508, -0.452254,
//        -0.146946, 0.154508, -0.452254,
//        0.125, 0.293893, -0.38471,
//        0.146946, 0.154508, -0.452254,
//        0.125, 0.293893, -0.38471,
//        0.327254, 0.293893, -0.237764,
//        0.38471, 0.154508, -0.279509,
//        0.146946, 0.154508, -0.452254,
//        0.327254, 0.293893, -0.237764,
//        0.38471, 0.154508, -0.279509,
//        0.327254, 0.293893, -0.237764,
//        0.404509, 0.293893, 7.07265e-08,
//        0.475528, 0.154508, 8.3144e-08,
//        0.38471, 0.154508, -0.279509,
//        0.404509, 0.293893, 7.07265e-08,
//        0.5, -0, 0,
//        0.475528, 0.154508, 0,
//        0.38471, 0.154508, 0.279509,
//        0.404509, -0, 0.293893,
//        0.5, -0, 0,
//        0.38471, 0.154508, 0.279509,
//        0.404509, -0, 0.293893,
//        0.38471, 0.154508, 0.279509,
//        0.146946, 0.154508, 0.452254,
//        0.154508, -0, 0.475528,
//        0.404509, -0, 0.293893,
//        0.146946, 0.154508, 0.452254,
//        0.154508, -0, 0.475528,
//        0.146946, 0.154508, 0.452254,
//        -0.146946, 0.154508, 0.452254,
//        -0.154509, -0, 0.475528,
//        0.154508, -0, 0.475528,
//        -0.146946, 0.154508, 0.452254,
//        -0.154509, -0, 0.475528,
//        -0.146946, 0.154508, 0.452254,
//        -0.38471, 0.154508, 0.279508,
//        -0.404509, -0, 0.293893,
//        -0.154509, -0, 0.475528,
//        -0.38471, 0.154508, 0.279508,
//        -0.404509, -0, 0.293893,
//        -0.38471, 0.154508, 0.279508,
//        -0.475528, 0.154508, -4.1572e-08,
//        -0.5, -0, -4.37114e-08,
//        -0.404509, -0, 0.293893,
//        -0.475528, 0.154508, -4.1572e-08,
//        -0.5, -0, -4.37114e-08,
//        -0.475528, 0.154508, -4.1572e-08,
//        -0.38471, 0.154508, -0.279509,
//        -0.404508, -0, -0.293893,
//        -0.5, -0, -4.37114e-08,
//        -0.38471, 0.154508, -0.279509,
//        -0.404508, -0, -0.293893,
//        -0.38471, 0.154508, -0.279509,
//        -0.146946, 0.154508, -0.452254,
//        -0.154509, -0, -0.475528,
//        -0.404508, -0, -0.293893,
//        -0.146946, 0.154508, -0.452254,
//        -0.154509, -0, -0.475528,
//        -0.146946, 0.154508, -0.452254,
//        0.146946, 0.154508, -0.452254,
//        0.154509, -0, -0.475528,
//        -0.154509, -0, -0.475528,
//        0.146946, 0.154508, -0.452254,
//        0.154509, -0, -0.475528,
//        0.146946, 0.154508, -0.452254,
//        0.38471, 0.154508, -0.279509,
//        0.404508, -0, -0.293893,
//        0.154509, -0, -0.475528,
//        0.38471, 0.154508, -0.279509,
//        0.404508, -0, -0.293893,
//        0.38471, 0.154508, -0.279509,
//        0.475528, 0.154508, 8.3144e-08,
//        0.5, -0, 8.74228e-08,
//        0.404508, -0, -0.293893,
//        0.475528, 0.154508, 8.3144e-08,
//        0.475528, -0.154509, 0,
//        0.5, -0, 0,
//        0.404509, -0, 0.293893,
//        0.38471, -0.154509, 0.279508,
//        0.475528, -0.154509, 0,
//        0.404509, -0, 0.293893,
//        0.38471, -0.154509, 0.279508,
//        0.404509, -0, 0.293893,
//        0.154508, -0, 0.475528,
//        0.146946, -0.154509, 0.452254,
//        0.38471, -0.154509, 0.279508,
//        0.154508, -0, 0.475528,
//        0.146946, -0.154509, 0.452254,
//        0.154508, -0, 0.475528,
//        -0.154509, -0, 0.475528,
//        -0.146946, -0.154509, 0.452254,
//        0.146946, -0.154509, 0.452254,
//        -0.154509, -0, 0.475528,
//        -0.146946, -0.154509, 0.452254,
//        -0.154509, -0, 0.475528,
//        -0.404509, -0, 0.293893,
//        -0.38471, -0.154509, 0.279508,
//        -0.146946, -0.154509, 0.452254,
//        -0.404509, -0, 0.293893,
//        -0.38471, -0.154509, 0.279508,
//        -0.404509, -0, 0.293893,
//        -0.5, -0, -4.37114e-08,
//        -0.475528, -0.154509, -4.1572e-08,
//        -0.38471, -0.154509, 0.279508,
//        -0.5, -0, -4.37114e-08,
//        -0.475528, -0.154509, -4.1572e-08,
//        -0.5, -0, -4.37114e-08,
//        -0.404508, -0, -0.293893,
//        -0.38471, -0.154509, -0.279509,
//        -0.475528, -0.154509, -4.1572e-08,
//        -0.404508, -0, -0.293893,
//        -0.38471, -0.154509, -0.279509,
//        -0.404508, -0, -0.293893,
//        -0.154509, -0, -0.475528,
//        -0.146946, -0.154509, -0.452254,
//        -0.38471, -0.154509, -0.279509,
//        -0.154509, -0, -0.475528,
//        -0.146946, -0.154509, -0.452254,
//        -0.154509, -0, -0.475528,
//        0.154509, -0, -0.475528,
//        0.146946, -0.154509, -0.452254,
//        -0.146946, -0.154509, -0.452254,
//        0.154509, -0, -0.475528,
//        0.146946, -0.154509, -0.452254,
//        0.154509, -0, -0.475528,
//        0.404508, -0, -0.293893,
//        0.38471, -0.154509, -0.279509,
//        0.146946, -0.154509, -0.452254,
//        0.404508, -0, -0.293893,
//        0.38471, -0.154509, -0.279509,
//        0.404508, -0, -0.293893,
//        0.5, -0, 8.74228e-08,
//        0.475528, -0.154509, 8.3144e-08,
//        0.38471, -0.154509, -0.279509,
//        0.5, -0, 8.74228e-08,
//        0.404509, -0.293893, 0,
//        0.475528, -0.154509, 0,
//        0.38471, -0.154509, 0.279508,
//        0.327254, -0.293893, 0.237764,
//        0.404509, -0.293893, 0,
//        0.38471, -0.154509, 0.279508,
//        0.327254, -0.293893, 0.237764,
//        0.38471, -0.154509, 0.279508,
//        0.146946, -0.154509, 0.452254,
//        0.125, -0.293893, 0.38471,
//        0.327254, -0.293893, 0.237764,
//        0.146946, -0.154509, 0.452254,
//        0.125, -0.293893, 0.38471,
//        0.146946, -0.154509, 0.452254,
//        -0.146946, -0.154509, 0.452254,
//        -0.125, -0.293893, 0.38471,
//        0.125, -0.293893, 0.38471,
//        -0.146946, -0.154509, 0.452254,
//        -0.125, -0.293893, 0.38471,
//        -0.146946, -0.154509, 0.452254,
//        -0.38471, -0.154509, 0.279508,
//        -0.327254, -0.293893, 0.237764,
//        -0.125, -0.293893, 0.38471,
//        -0.38471, -0.154509, 0.279508,
//        -0.327254, -0.293893, 0.237764,
//        -0.38471, -0.154509, 0.279508,
//        -0.475528, -0.154509, -4.1572e-08,
//        -0.404509, -0.293893, -3.53633e-08,
//        -0.327254, -0.293893, 0.237764,
//        -0.475528, -0.154509, -4.1572e-08,
//        -0.404509, -0.293893, -3.53633e-08,
//        -0.475528, -0.154509, -4.1572e-08,
//        -0.38471, -0.154509, -0.279509,
//        -0.327254, -0.293893, -0.237764,
//        -0.404509, -0.293893, -3.53633e-08,
//        -0.38471, -0.154509, -0.279509,
//        -0.327254, -0.293893, -0.237764,
//        -0.38471, -0.154509, -0.279509,
//        -0.146946, -0.154509, -0.452254,
//        -0.125, -0.293893, -0.38471,
//        -0.327254, -0.293893, -0.237764,
//        -0.146946, -0.154509, -0.452254,
//        -0.125, -0.293893, -0.38471,
//        -0.146946, -0.154509, -0.452254,
//        0.146946, -0.154509, -0.452254,
//        0.125, -0.293893, -0.38471,
//        -0.125, -0.293893, -0.38471,
//        0.146946, -0.154509, -0.452254,
//        0.125, -0.293893, -0.38471,
//        0.146946, -0.154509, -0.452254,
//        0.38471, -0.154509, -0.279509,
//        0.327254, -0.293893, -0.237764,
//        0.125, -0.293893, -0.38471,
//        0.38471, -0.154509, -0.279509,
//        0.327254, -0.293893, -0.237764,
//        0.38471, -0.154509, -0.279509,
//        0.475528, -0.154509, 8.3144e-08,
//        0.404509, -0.293893, 7.07265e-08,
//        0.327254, -0.293893, -0.237764,
//        0.475528, -0.154509, 8.3144e-08,
//        0.293893, -0.404509, 0,
//        0.404509, -0.293893, 0,
//        0.327254, -0.293893, 0.237764,
//        0.237764, -0.404509, 0.172746,
//        0.293893, -0.404509, 0,
//        0.327254, -0.293893, 0.237764,
//        0.237764, -0.404509, 0.172746,
//        0.327254, -0.293893, 0.237764,
//        0.125, -0.293893, 0.38471,
//        0.0908178, -0.404509, 0.279509,
//        0.237764, -0.404509, 0.172746,
//        0.125, -0.293893, 0.38471,
//        0.0908178, -0.404509, 0.279509,
//        0.125, -0.293893, 0.38471,
//        -0.125, -0.293893, 0.38471,
//        -0.0908178, -0.404509, 0.279508,
//        0.0908178, -0.404509, 0.279509,
//        -0.125, -0.293893, 0.38471,
//        -0.0908178, -0.404509, 0.279508,
//        -0.125, -0.293893, 0.38471,
//        -0.327254, -0.293893, 0.237764,
//        -0.237764, -0.404509, 0.172746,
//        -0.0908178, -0.404509, 0.279508,
//        -0.327254, -0.293893, 0.237764,
//        -0.237764, -0.404509, 0.172746,
//        -0.327254, -0.293893, 0.237764,
//        -0.404509, -0.293893, -3.53633e-08,
//        -0.293893, -0.404509, -2.56929e-08,
//        -0.237764, -0.404509, 0.172746,
//        -0.404509, -0.293893, -3.53633e-08,
//        -0.293893, -0.404509, -2.56929e-08,
//        -0.404509, -0.293893, -3.53633e-08,
//        -0.327254, -0.293893, -0.237764,
//        -0.237764, -0.404509, -0.172746,
//        -0.293893, -0.404509, -2.56929e-08,
//        -0.327254, -0.293893, -0.237764,
//        -0.237764, -0.404509, -0.172746,
//        -0.327254, -0.293893, -0.237764,
//        -0.125, -0.293893, -0.38471,
//        -0.0908178, -0.404509, -0.279508,
//        -0.237764, -0.404509, -0.172746,
//        -0.125, -0.293893, -0.38471,
//        -0.0908178, -0.404509, -0.279508,
//        -0.125, -0.293893, -0.38471,
//        0.125, -0.293893, -0.38471,
//        0.0908179, -0.404509, -0.279508,
//        -0.0908178, -0.404509, -0.279508,
//        0.125, -0.293893, -0.38471,
//        0.0908179, -0.404509, -0.279508,
//        0.125, -0.293893, -0.38471,
//        0.327254, -0.293893, -0.237764,
//        0.237764, -0.404509, -0.172746,
//        0.0908179, -0.404509, -0.279508,
//        0.327254, -0.293893, -0.237764,
//        0.237764, -0.404509, -0.172746,
//        0.327254, -0.293893, -0.237764,
//        0.404509, -0.293893, 7.07265e-08,
//        0.293893, -0.404509, 5.13858e-08,
//        0.237764, -0.404509, -0.172746,
//        0.404509, -0.293893, 7.07265e-08,
//        0.154509, -0.475528, 0,
//        0.293893, -0.404509, 0,
//        0.237764, -0.404509, 0.172746,
//        0.125, -0.475528, 0.0908178,
//        0.154509, -0.475528, 0,
//        0.237764, -0.404509, 0.172746,
//        0.125, -0.475528, 0.0908178,
//        0.237764, -0.404509, 0.172746,
//        0.0908178, -0.404509, 0.279509,
//        0.0477458, -0.475528, 0.146946,
//        0.125, -0.475528, 0.0908178,
//        0.0908178, -0.404509, 0.279509,
//        0.0477458, -0.475528, 0.146946,
//        0.0908178, -0.404509, 0.279509,
//        -0.0908178, -0.404509, 0.279508,
//        -0.0477458, -0.475528, 0.146946,
//        0.0477458, -0.475528, 0.146946,
//        -0.0908178, -0.404509, 0.279508,
//        -0.0477458, -0.475528, 0.146946,
//        -0.0908178, -0.404509, 0.279508,
//        -0.237764, -0.404509, 0.172746,
//        -0.125, -0.475528, 0.0908178,
//        -0.0477458, -0.475528, 0.146946,
//        -0.237764, -0.404509, 0.172746,
//        -0.125, -0.475528, 0.0908178,
//        -0.237764, -0.404509, 0.172746,
//        -0.293893, -0.404509, -2.56929e-08,
//        -0.154509, -0.475528, -1.35076e-08,
//        -0.125, -0.475528, 0.0908178,
//        -0.293893, -0.404509, -2.56929e-08,
//        -0.154509, -0.475528, -1.35076e-08,
//        -0.293893, -0.404509, -2.56929e-08,
//        -0.237764, -0.404509, -0.172746,
//        -0.125, -0.475528, -0.0908179,
//        -0.154509, -0.475528, -1.35076e-08,
//        -0.237764, -0.404509, -0.172746,
//        -0.125, -0.475528, -0.0908179,
//        -0.237764, -0.404509, -0.172746,
//        -0.0908178, -0.404509, -0.279508,
//        -0.0477458, -0.475528, -0.146946,
//        -0.125, -0.475528, -0.0908179,
//        -0.0908178, -0.404509, -0.279508,
//        -0.0477458, -0.475528, -0.146946,
//        -0.0908178, -0.404509, -0.279508,
//        0.0908179, -0.404509, -0.279508,
//        0.0477458, -0.475528, -0.146946,
//        -0.0477458, -0.475528, -0.146946,
//        0.0908179, -0.404509, -0.279508,
//        0.0477458, -0.475528, -0.146946,
//        0.0908179, -0.404509, -0.279508,
//        0.237764, -0.404509, -0.172746,
//        0.125, -0.475528, -0.0908178,
//        0.0477458, -0.475528, -0.146946,
//        0.237764, -0.404509, -0.172746,
//        0.125, -0.475528, -0.0908178,
//        0.237764, -0.404509, -0.172746,
//        0.293893, -0.404509, 5.13858e-08,
//        0.154509, -0.475528, 2.70151e-08,
//        0.125, -0.475528, -0.0908178,
//        0.293893, -0.404509, 5.13858e-08,
//        -2.18557e-08, -0.5, -0,
//        0.154509, -0.475528, 0,
//        0.125, -0.475528, 0.0908178,
//        -1.76816e-08, -0.5, -1.28465e-08,
//        -2.18557e-08, -0.5, -0,
//        0.125, -0.475528, 0.0908178,
//        -1.76816e-08, -0.5, -1.28465e-08,
//        0.125, -0.475528, 0.0908178,
//        0.0477458, -0.475528, 0.146946,
//        -6.75378e-09, -0.5, -2.0786e-08,
//        -1.76816e-08, -0.5, -1.28465e-08,
//        0.0477458, -0.475528, 0.146946,
//        -6.75378e-09, -0.5, -2.0786e-08,
//        0.0477458, -0.475528, 0.146946,
//        -0.0477458, -0.475528, 0.146946,
//        6.75378e-09, -0.5, -2.0786e-08,
//        -6.75378e-09, -0.5, -2.0786e-08,
//        -0.0477458, -0.475528, 0.146946,
//        6.75378e-09, -0.5, -2.0786e-08,
//        -0.0477458, -0.475528, 0.146946,
//        -0.125, -0.475528, 0.0908178,
//        1.76816e-08, -0.5, -1.28465e-08,
//        6.75378e-09, -0.5, -2.0786e-08,
//        -0.125, -0.475528, 0.0908178,
//        1.76816e-08, -0.5, -1.28465e-08,
//        -0.125, -0.475528, 0.0908178,
//        -0.154509, -0.475528, -1.35076e-08,
//        2.18557e-08, -0.5, 1.91069e-15,
//        1.76816e-08, -0.5, -1.28465e-08,
//        -0.154509, -0.475528, -1.35076e-08,
//        2.18557e-08, -0.5, 1.91069e-15,
//        -0.154509, -0.475528, -1.35076e-08,
//        -0.125, -0.475528, -0.0908179,
//        1.76816e-08, -0.5, 1.28465e-08,
//        2.18557e-08, -0.5, 1.91069e-15,
//        -0.125, -0.475528, -0.0908179,
//        1.76816e-08, -0.5, 1.28465e-08,
//        -0.125, -0.475528, -0.0908179,
//        -0.0477458, -0.475528, -0.146946,
//        6.75378e-09, -0.5, 2.0786e-08,
//        1.76816e-08, -0.5, 1.28465e-08,
//        -0.0477458, -0.475528, -0.146946,
//        6.75378e-09, -0.5, 2.0786e-08,
//        -0.0477458, -0.475528, -0.146946,
//        0.0477458, -0.475528, -0.146946,
//        -6.75378e-09, -0.5, 2.0786e-08,
//        6.75378e-09, -0.5, 2.0786e-08,
//        0.0477458, -0.475528, -0.146946,
//        -6.75378e-09, -0.5, 2.0786e-08,
//        0.0477458, -0.475528, -0.146946,
//        0.125, -0.475528, -0.0908178,
//        -1.76816e-08, -0.5, 1.28465e-08,
//        -6.75378e-09, -0.5, 2.0786e-08,
//        0.125, -0.475528, -0.0908178,
//        -1.76816e-08, -0.5, 1.28465e-08,
//        0.125, -0.475528, -0.0908178,
//        0.154509, -0.475528, 2.70151e-08,
//        -2.18557e-08, -0.5, -3.82137e-15,
//        -1.76816e-08, -0.5, 1.28465e-08,
//        0.154509, -0.475528, 2.70151e-08,
//    };

//    for(int i = 0; i < (600*3); i++)
//    {
//        vertexBufferData[i] *= 2.0f;
//    }

//    // VAO init
//    glGenVertexArrays(1, &m_vaoID);
//    glBindVertexArray(m_vaoID);

//    // Vertex buffer init
//    glGenBuffers(1, &m_vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

//    // Give our vertices to OpenGL.
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

//    // Expose vertices to shader
//    glEnableVertexAttribArray(vertexLocation);
//    glVertexAttribPointer(
//       vertexLocation,
//       3,                  // num vertices per element (3 for triangle)
//       GL_FLOAT,           // type
//       GL_FALSE,           // normalized?
//       0,                  // stride
//       (void*)0            // array buffer offset
//    );

//    glEnableVertexAttribArray(normalLocation);
//    glVertexAttribPointer(
//       normalLocation,
//       3,                  // num vertices per element (3 for triangle)
//       GL_FLOAT,           // type
//       GL_TRUE,            // normalized?
//       0,                  // stride
//       (void*)0            // array buffer offset
//    );

//    //Clean up -- unbind things
//    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindVertexArray(0);
//}

//void Sphere::draw(){
//    if (!m_isInitialized){
//        std::cout << "You must call init() before you can draw!" << std::endl;
//    } else{
//        // Rebind your vertex array and draw the triangles
//        glBindVertexArray(m_vaoID);
//        glDrawArrays(GL_TRIANGLES, 0, NUM_TRIS*3);
//        glBindVertexArray(0);
//    }
//}


#include "Sphere.h"
#include "math.h"


Sphere::Sphere(int param1, int param2, int param3, const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
    : Shape(param1, param2, param3)
{
    m_param1 = param1;
    m_param2 = param2;
    m_param3 = param3;


    int n_per_slice = 2* m_param1 - 2;
    m_n_triangle = n_per_slice * m_param2;
    auto_compute_m_n(m_n_triangle);
    m_n_vertexData += m_n_triangle * 3 * 2;
    //m_radius = 0.5;
    init(vertexLocation, normalLocation, textureLocation);
}

Sphere::~Sphere()
{
//    glDeleteBuffers(1, &m_vboID);
//    glDeleteVertexArrays(1, &m_vaoID);
//    delete []m_vertexData;
//    m_vertexData = 0;
}


void Sphere::init(const GLuint vertexLocation, const GLuint normalLocation, const GLuint textureLocation)
{
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    // Initialize the vertex buffer object.

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    m_vertexData = new GLfloat[m_n_vertexData];

    float phi = 1.0 * M_PI / m_param1;
    float theta = 2.0 * M_PI / m_param2;

    int n_per_slice = 2 * m_param1 - 2;

    glm::vec3 vertexTop = glm::vec3(0.0, m_radius, 0.0);
    glm::vec3 vertexBottom = glm::vec3(0.0, -m_radius, 0.0);
    glm::vec3 norm_top = glm::vec3(0.0, 1, 0.0);
    glm::vec3 norm_bottom = glm::vec3(0.0, -1, 0.0);

    glm::vec3 lower_right;
    glm::vec3 lower_left;
    glm::vec3 top_right;
    glm::vec3 top_left;
    glm::vec3 norm_lower_right;
    glm::vec3 norm_lower_left;
    glm::vec3 norm_top_right;
    glm::vec3 norm_top_left;

    glm::vec2 tex_top;
    glm::vec2 tex_bottom;
    glm::vec2 tex_lower_right;
    glm::vec2 tex_lower_left;
    glm::vec2 tex_top_right;
    glm::vec2 tex_top_left;

    int index;
    int i, j;
    float cur_theta, next_theta, cur_phi, next_phi, phi_bottom;

    for(i = 0; i < m_param2; i++)
    {
        cur_theta = i * theta;
        next_theta = (i + 1) * theta;
        index = i * n_per_slice * 3 * ( 3 * 2 + 2 );

        // triangle on top
        lower_right = getSphereCoord(cur_theta, phi);
        lower_left = getSphereCoord(next_theta, phi);

        norm_lower_right = getSphereNorm(cur_theta, phi);
        norm_lower_left = getSphereNorm(next_theta, phi);

        tex_top = getShapeUV(glm::vec4(vertexTop, 1.0f));
        tex_lower_right = getShapeUV(glm::vec4(lower_right, 1.0f));
        tex_lower_left = getShapeUV(glm::vec4(lower_left, 1.0f));

        insert2vertexData_tri(index, vertexTop, lower_left, lower_right);
        insert2vertexData_tri(index+3, norm_top, norm_lower_left, norm_lower_right);
        insert2vertexData_tri2(index+6, tex_top, tex_lower_left, tex_lower_right);



        // triangle on bottom
        index += 3 * ( 3 * 2 + 2);

        phi_bottom = M_PI - phi;

        top_right = getSphereCoord(cur_theta, phi_bottom);
        top_left = getSphereCoord(next_theta, phi_bottom);

        norm_top_right = getSphereNorm(cur_theta, phi_bottom);
        norm_top_left = getSphereNorm(next_theta, phi_bottom);

        tex_bottom = getShapeUV(glm::vec4(vertexBottom, 1.0f));
        tex_top_right = getShapeUV(glm::vec4(top_right, 1.0f));
        tex_top_left = getShapeUV(glm::vec4(top_left, 1.0f));

        insert2vertexData_tri(index, vertexBottom, top_right, top_left);
        insert2vertexData_tri(index+3, norm_bottom, norm_top_right, norm_top_left);
        insert2vertexData_tri2(index+6, tex_bottom, tex_top_right, tex_top_left);


        index += 3 * (3 * 2 + 2);

        for(j = 1; j< (m_param1-1); j++)
        {
            cur_phi = j * phi;
            next_phi = (j + 1) * phi;
            top_right = getSphereCoord(cur_theta, cur_phi);
            top_left = getSphereCoord(next_theta, cur_phi);
            lower_left = getSphereCoord(next_theta, next_phi);
            lower_right = getSphereCoord(cur_theta, next_phi);

            norm_top_right = getSphereNorm(cur_theta, cur_phi);
            norm_top_left = getSphereNorm(next_theta, cur_phi);
            norm_lower_left = getSphereNorm(next_theta, next_phi);
            norm_lower_right = getSphereNorm(cur_theta, next_phi);

            tex_top_right = getShapeUV(glm::vec4(top_right, 1.0f));
            tex_top_left = getShapeUV(glm::vec4(top_left, 1.0f));
            tex_lower_left = getShapeUV(glm::vec4(lower_left, 1.0f));
            tex_lower_right = getShapeUV(glm::vec4(lower_right, 1.0f));


            insert2vertexData_rec(index, top_right, top_left, lower_left, lower_right);
            insert2vertexData_rec(index+3, norm_top_right, norm_top_left, norm_lower_left, norm_lower_right);
            insert2vertexData_rec2(index+6, tex_top_right, tex_top_left, tex_lower_left, tex_lower_right);


            index += 3 * ( 3 * 2  + 2 )* 2;
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




glm::vec3 Sphere::getSphereNorm(float theta, float phi)
{
    glm::vec3 norm = glm::vec3(sin(phi)*cos(theta), cos(phi), sin(phi)*sin(theta));

    float theta_i = 2.0 * M_PI / m_param2;

//    if(((int)(theta/theta_i))%5 ==0)
//    {
//        norm = glm::vec3(-1.0, 0.0, 0.0);
//    }


    return norm;
}



glm::vec3 Sphere::getSphereCoord(float theta, float phi)
{
    return glm::vec3(m_radius * sin(phi)*cos(theta), m_radius * cos(phi), m_radius * sin(phi)*sin(theta));
}



float Sphere::getIntersect(glm::vec4 eye_pos, glm::vec4 ray_dir)
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

glm::vec4 Sphere::getShapeNormal(glm::vec4 intersect_point)
{
    glm::vec4 norm = glm::vec4(intersect_point.x, intersect_point.y,
                               intersect_point.z, 0.0);
    return glm::normalize(norm);

}




glm::vec2 Sphere::getShapeUV(glm::vec4 intersect_point)
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

