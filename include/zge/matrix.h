/*
 * matrix.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/27/2012
 */
 
#pragma once

#include "zge/gl_includes.h"
#include "zge/vector.h"

#include <string>

namespace zge {

template <unsigned ROWS, unsigned COLS>
class ZMatrix {
public:
    GLfloat matrix[ROWS * COLS];
    
    ZMatrix();
    ZMatrix(const ZMatrix &copy);
    ZMatrix(GLfloat array[]);
    
    /** Operators **/
    GLfloat operator[](int index);
    ZMatrix operator*(const ZMatrix &other);
    ZMatrix& operator*=(const ZMatrix &other);
    // TODO: More arithmetic operators
    
    /** Transforms **/
    static ZMatrix identity();
    
    /** Description **/
    std::string getDescription();
};
typedef ZMatrix<3, 3> ZMatrix3;

class ZMatrix4 : public ZMatrix<4, 4> {
public:
    ZMatrix4() : ZMatrix() {}
    ZMatrix4(const ZMatrix &copy) : ZMatrix(copy) {}
    ZMatrix4(GLfloat array[]) : ZMatrix(array) {}
    
    /** Transforms **/
    static ZMatrix4 translation(float tx, float ty, float tz);
    static ZMatrix4 rotation(float degrees, float x, float y, float z);
    static ZMatrix4 scale(float sx, float sy, float sz);
    
    /** Geometry **/
    static ZMatrix4 frustum(float left, float right, float bottom, float top,
                           float nearZ, float farZ);
    static ZMatrix4 perspective(float fovy, float aspect, float nearZ, float farZ);
    static ZMatrix4 lookAt(ZVec3 eye, ZVec3 center, ZVec3 up); 
};

} // namespace zge
