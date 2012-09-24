/*
 * matrix.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/27/2012
 */
 
#include "zge/matrix.h"
#include "zge/exception.h"
#include "zge/util.h"
#include "zge/vector.h"

#include <complex>
#include <cstring>
#include <cmath>
#include <iostream>
#include <sstream>

namespace zge {

template <unsigned R, unsigned C>
matrix_base<R, C>::matrix_base(GLfloat arr[])
{
    if (arr != nullptr) {
        for (unsigned i = 0; i < R * C; ++i) {
            array[i] = arr[i];
        }
    } else {
        memset(array, 0, R * C * sizeof(GLfloat));
    }
}

template <unsigned R, unsigned C>
matrix_base<R, C>::matrix_base(const matrix_base &copy)
{
    this->copy(copy);
}

template <unsigned R, unsigned C>
matrix_base<R, C>::matrix_base(matrix_base<R, C> &&move)
{
    std::swap(array, move.array);
}

template <unsigned R, unsigned C>
matrix_base<R, C>& matrix_base<R, C>::operator=(const matrix_base<R, C> &other)
{
    if (this != &other) {
        copy(other);
    }
    
    return *this;
}

template <unsigned R, unsigned C>
matrix_base<R, C>& matrix_base<R, C>::operator=(matrix_base<R, C> &&other)
{
    if (this != &other) {
        std::swap(array, other.array);
    }
    
    return *this;
}


#pragma mark - Operators

template <unsigned R, unsigned C>
GLfloat matrix_base<R, C>::operator[](int index)
{
    return array[index];
}

template <unsigned R, unsigned C>
matrix_base<R, C> matrix_base<R, C>::operator*(const matrix_base<R, C> &other)
{
    return multiply(other);
}

template <unsigned R, unsigned C>
matrix_base<R, C>& matrix_base<R, C>::operator*=(const matrix_base<R, C> &other)
{
    return (*this = (*this * other));
}


#pragma mark - Data

template <unsigned R, unsigned C>
void matrix_base<R, C>::copy(const matrix_base<R, C> &copy)
{
    for (unsigned i = 0; i < R * C; ++i) {
        array[i] = copy.array[i];
    }
}


#pragma mark - Math

template <unsigned R, unsigned C>
matrix_base<R, C> matrix_base<R, C>::multiply(const matrix_base<R, C> &other)
{
    if (R != C) {
        not_implemented_exception e;
        e.extra_info = "Only square matrices can be multiplied at the moment.";
        throw e;
    }
    
    unsigned n = R;
    matrix_base<R, C> t;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            for (unsigned k = 0; k < n; ++k) {
                t.array[i * n + j] += array[i * n + k] * other.array[k * n + j];
            }
        }
    }
    
    return t;
}


#pragma mark - Transforms

template <unsigned R, unsigned C>
matrix_base<R, C> matrix_base<R, C>::identity()
{
    if (R != C) {
        throw "Not a square matrix. Cannot create identity.";
    }
    
    matrix_base<R, C> matrix;
    for (unsigned row = 0, col = 0; row < R && col < C; ++row, ++col) {
        matrix.array[row * C + col] = 1.0;
    }
    
    return matrix;
}

matrix<4, 4> matrix<4, 4>::translation(float tx, float ty, float tz)
{
    matrix<4, 4> mat = matrix<4, 4>::identity();
    mat.array[12] = tx;
    mat.array[13] = ty;
    mat.array[14] = tz;
    
    return mat;
}

matrix<4, 4> matrix<4, 4>::rotation(float degrees, float x, float y, float z)
{
    float radians = util::degrees_to_radians(degrees);
    
    vec3 v = vec3(x, y, z).normalize();
    float cos = std::cos(radians);
    float cosp = 1.0f - cos;
    float sin = std::sin(radians);
    
    float m[16] = {
        cos + cosp * v.x * v.x,
        cosp * v.x * v.y + v.z * sin,
        cosp * v.x * v.z - v.y * sin,
        0.0f,
        cosp * v.x * v.y - v.z * sin,
        cos + cosp * v.y * v.y,
        cosp * v.y * v.z + v.x * sin,
        0.0f,
        cosp * v.x * v.z + v.y * sin,
        cosp * v.y * v.z - v.x * sin,
        cos + cosp * v.z * v.z,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f
    };
    
    return matrix<4, 4>(m);
}

matrix<4, 4> matrix<4, 4>::scale(float sx, float sy, float sz)
{
    matrix<4, 4> mat = matrix<4, 4>::identity();
    mat.array[0]   = sx;
    mat.array[5]   = sy;
    mat.array[10]  = sz;
    
    return mat;
}


#pragma mark - Geometry

matrix<4, 4> matrix<4, 4>::frustum(float left, float right, float bottom, float top,
                           float nearZ, float farZ)
{
    matrix<4, 4> mat = matrix<4, 4>::identity();
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    
    mat.array[0] = 2.0f * nearZ / deltaX;
    mat.array[1] = mat.array[2] = mat.array[3] = 0.0f;
    
    mat.array[4] = mat.array[6] = mat.array[7] = 0.0f;
    mat.array[5] = 2.0f * nearZ / deltaY;
    
    mat.array[8] = (right + left) / deltaX;
    mat.array[9] = (top + bottom) / deltaY;
    mat.array[10] = -(nearZ + farZ) / deltaZ;
    mat.array[11] = -1.0f;
    
    mat.array[12] = mat.array[14] = mat.array[15] = 0.0f;
    mat.array[14] = -2.0f * nearZ * farZ / deltaZ;
    
    return mat;
}

matrix<4, 4> matrix<4, 4>::perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float fheight   = std::tan(fovy / 360.0 * M_PI) * nearZ;
    float fwidth    = fheight * aspect;
    
    matrix<4, 4> frust = matrix<4, 4>::frustum(-fwidth, fwidth, -fheight, fheight, nearZ, farZ);
    return frust;
}

matrix<4, 4> matrix<4, 4>::lookat(vec3 eye, vec3 center, vec3 up)
{
    vec3 n = (eye + center.negate()).normalize();
    vec3 u = (up.cross(n)).normalize();
    vec3 v = n.cross(u);
    
    float m[16] = {
        u.x, v.x, n.x, 0.0f,
        u.y, v.y, n.y, 0.0f,
        u.z, v.z, n.z, 0.0f,
        u.negate() * eye, v.negate() * eye, n.negate() * eye, 1.0f
    };
    
    return matrix<4, 4>(m);
}


#pragma mark - Description

template <unsigned R, unsigned C>
std::string matrix_base<R, C>::get_description()
{
    std::ostringstream oss;
    for (unsigned i = 0; i < R * C; ++i) {
        if (i != 0 && i % C == 0) {
            oss << '\n';
        } else if (i != 0) {
            oss << '\t';
        }
        
        oss << array[i];
    }
    
    return oss.str();
}


// To avoid linker errors
template class matrix_base<1, 1>;
template class matrix_base<1, 2>;
template class matrix_base<1, 3>;
template class matrix_base<1, 4>;
template class matrix_base<1, 5>;
template class matrix_base<1, 6>;
template class matrix_base<2, 1>;
template class matrix_base<2, 2>;
template class matrix_base<2, 3>;
template class matrix_base<2, 4>;
template class matrix_base<2, 5>;
template class matrix_base<2, 6>;
template class matrix_base<3, 1>;
template class matrix_base<3, 2>;
template class matrix_base<3, 3>;
template class matrix_base<3, 4>;
template class matrix_base<3, 5>;
template class matrix_base<3, 6>;
template class matrix_base<4, 1>;
template class matrix_base<4, 2>;
template class matrix_base<4, 3>;
template class matrix_base<4, 4>;
template class matrix_base<4, 5>;
template class matrix_base<4, 6>;
template class matrix_base<5, 1>;
template class matrix_base<5, 2>;
template class matrix_base<5, 3>;
template class matrix_base<5, 4>;
template class matrix_base<5, 5>;
template class matrix_base<5, 6>;
template class matrix_base<6, 1>;
template class matrix_base<6, 2>;
template class matrix_base<6, 3>;
template class matrix_base<6, 4>;
template class matrix_base<6, 5>;
template class matrix_base<6, 6>;

} // namespace zge
