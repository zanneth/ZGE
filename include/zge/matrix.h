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
class ZMatrixBase {
public:
    GLfloat matrix[ROWS * COLS];
    
    explicit ZMatrixBase(GLfloat array[] = nullptr);
    ZMatrixBase(const ZMatrixBase &copy);
    ZMatrixBase(ZMatrixBase &&move);
    ZMatrixBase& operator=(const ZMatrixBase &other);
    ZMatrixBase& operator=(ZMatrixBase &&other);
    
    /** Operators **/
    GLfloat operator[](int index);
    ZMatrixBase operator*(const ZMatrixBase &other);
    ZMatrixBase& operator*=(const ZMatrixBase &other);
    // TODO: More arithmetic operators
    
    /** Data **/
    void copy(const ZMatrixBase &copy);
    
    /** Math **/
    ZMatrixBase multiply(const ZMatrixBase &other);
    
    /** Transforms **/
    static ZMatrixBase identity();
    
    /** Description **/
    std::string getDescription();
};

template <unsigned ROWS, unsigned COLS>
class ZMatrix : public ZMatrixBase<ROWS, COLS> {
public:
    using ZMatrixBase<ROWS, COLS>::ZMatrixBase;
};
typedef ZMatrix<3, 3> ZMatrix3;

template <>
class ZMatrix<4, 4> : public ZMatrixBase<4, 4> {
public:
    ZMatrix<4, 4>(GLfloat array[] = nullptr) : ZMatrixBase(array) {}
    ZMatrix<4, 4>(const ZMatrixBase &copy) : ZMatrixBase(copy) {}
    ZMatrix<4, 4>(ZMatrixBase &&move) : ZMatrixBase(move) {}
    
    /** Transforms **/
    static ZMatrix<4, 4> translation(float tx, float ty, float tz);
    static ZMatrix<4, 4> rotation(float degrees, float x, float y, float z);
    static ZMatrix<4, 4> scale(float sx, float sy, float sz);
    
    /** Geometry **/
    static ZMatrix<4, 4> frustum(float left, float right, float bottom, float top,
                           float nearZ, float farZ);
    static ZMatrix<4, 4> perspective(float fovy, float aspect, float nearZ, float farZ);
    static ZMatrix<4, 4> lookAt(ZVec3 eye, ZVec3 center, ZVec3 up); 
};
typedef ZMatrix<4, 4> ZMatrix4;

} // namespace zge
