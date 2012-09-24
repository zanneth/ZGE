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
class matrix_base {
public:
    GLfloat array[ROWS * COLS];
    
    explicit matrix_base(GLfloat arr[] = nullptr);
    matrix_base(const matrix_base &copy);
    matrix_base(matrix_base &&move);
    matrix_base& operator=(const matrix_base &other);
    matrix_base& operator=(matrix_base &&other);
    
    /** Operators **/
    GLfloat operator[](int index);
    matrix_base operator*(const matrix_base &other);
    matrix_base& operator*=(const matrix_base &other);
    // TODO: More arithmetic operators
    
    /** Data **/
    void copy(const matrix_base &copy);
    
    /** Math **/
    matrix_base multiply(const matrix_base &other);
    
    /** Transforms **/
    static matrix_base identity();
    
    /** Description **/
    std::string get_description();
};

template <unsigned ROWS, unsigned COLS>
class matrix : public matrix_base<ROWS, COLS> {
public:
    matrix<ROWS, COLS>(GLfloat arr[] = nullptr) : matrix_base<ROWS, COLS>(arr) {}
    matrix<ROWS, COLS>(const matrix &copy) : matrix_base<ROWS, COLS>(copy) {}
    matrix<ROWS, COLS>(matrix &&move) : matrix_base<ROWS, COLS>(move) {}
};
typedef matrix<3, 3> mat3;

template <>
class matrix<4, 4> : public matrix_base<4, 4> {
public:
    matrix<4, 4>(GLfloat arr[] = nullptr) : matrix_base(arr) {}
    matrix<4, 4>(const matrix_base &copy) : matrix_base(copy) {}
    matrix<4, 4>(matrix_base &&move) : matrix_base(move) {}
    
    /** Transforms **/
    static matrix<4, 4> translation(float tx, float ty, float tz);
    static matrix<4, 4> rotation(float degrees, float x, float y, float z);
    static matrix<4, 4> scale(float sx, float sy, float sz);
    
    /** Geometry **/
    static matrix<4, 4> frustum(float left, float right, float bottom, float top,
                           float nearZ, float farZ);
    static matrix<4, 4> perspective(float fovy, float aspect, float nearZ, float farZ);
    static matrix<4, 4> lookat(vec3 eye, vec3 center, vec3 up); 
};
typedef matrix<4, 4> mat4;

} // namespace zge
