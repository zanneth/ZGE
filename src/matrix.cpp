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
#include <sstream>

namespace zge {

template <unsigned R, unsigned C>
ZMatrixBase<R, C>::ZMatrixBase(GLfloat arr[])
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
ZMatrixBase<R, C>::ZMatrixBase(const ZMatrixBase &copy)
{
    this->copy(copy);
}

template <unsigned R, unsigned C>
ZMatrixBase<R, C>::ZMatrixBase(ZMatrixBase<R, C> &&move)
{
    std::swap(array, move.array);
}

template <unsigned R, unsigned C>
ZMatrixBase<R, C>& ZMatrixBase<R, C>::operator=(const ZMatrixBase<R, C> &other)
{
    if (this != &other) {
        copy(other);
    }
    
    return *this;
}

template <unsigned R, unsigned C>
ZMatrixBase<R, C>& ZMatrixBase<R, C>::operator=(ZMatrixBase<R, C> &&other)
{
    if (this != &other) {
        std::swap(array, other.array);
    }
    
    return *this;
}


#pragma mark - Operators

template <unsigned R, unsigned C>
GLfloat ZMatrixBase<R, C>::operator[](int index)
{
    return array[index];
}

template <unsigned R, unsigned C>
ZMatrixBase<R, C> ZMatrixBase<R, C>::operator*(const ZMatrixBase<R, C> &other)
{
    return multiply(other);
}

template <unsigned R, unsigned C>
ZMatrixBase<R, C>& ZMatrixBase<R, C>::operator*=(const ZMatrixBase<R, C> &other)
{
    return (*this = (*this * other));
}


#pragma mark - Data

template <unsigned R, unsigned C>
void ZMatrixBase<R, C>::copy(const ZMatrixBase<R, C> &copy)
{
    for (unsigned i = 0; i < R * C; ++i) {
        array[i] = copy.array[i];
    }
}


#pragma mark - Math

template <unsigned R, unsigned C>
ZMatrixBase<R, C> ZMatrixBase<R, C>::multiply(const ZMatrixBase<R, C> &other)
{
    if (R != C) {
        ZException e(NOT_IMPLEMENTED_EXCEPTION_CODE);
        e.extra_info = "Only square matrices can be multiplied at the moment.";
        throw e;
    }
    
    unsigned n = R;
    ZMatrixBase<R, C> t;
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
ZMatrixBase<R, C> ZMatrixBase<R, C>::identity()
{
    if (R != C) {
        throw "Not a square matrix. Cannot create identity.";
    }
    
    ZMatrixBase<R, C> matrix;
    for (unsigned row = 0, col = 0; row < R && col < C; ++row, ++col) {
        matrix.array[row * C + col] = 1.0;
    }
    
    return matrix;
}

ZMatrix<4, 4> ZMatrix<4, 4>::translation(float tx, float ty, float tz)
{
    ZMatrix<4, 4> mat = ZMatrix<4, 4>::identity();
    mat.array[12] = tx;
    mat.array[13] = ty;
    mat.array[14] = tz;
    
    return mat;
}

ZMatrix<4, 4> ZMatrix<4, 4>::rotation(float degrees, float x, float y, float z)
{
    float radians = ZUtil::degrees_to_radians(degrees);
    
    ZVec3 v = ZVec3(x, y, z).normalize();
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
    
    return ZMatrix<4, 4>(m);
}

ZMatrix<4, 4> ZMatrix<4, 4>::scale(float sx, float sy, float sz)
{
    ZMatrix<4, 4> mat = ZMatrix<4, 4>::identity();
    mat.array[0]   = sx;
    mat.array[5]   = sy;
    mat.array[10]  = sz;
    
    return mat;
}


#pragma mark - Geometry

ZMatrix<4, 4> ZMatrix<4, 4>::frustum(float left, float right, float bottom, float top,
                           float nearZ, float farZ)
{
    ZMatrix<4, 4> mat = ZMatrix<4, 4>::identity();
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

ZMatrix<4, 4> ZMatrix<4, 4>::perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float fheight   = std::tan(fovy / 360.0 * M_PI) * nearZ;
    float fwidth    = fheight * aspect;
    
    ZMatrix<4, 4> frust = ZMatrix<4, 4>::frustum(-fwidth, fwidth, -fheight, fheight, nearZ, farZ);
    return frust;
}

ZMatrix<4, 4> ZMatrix<4, 4>::lookat(ZVec3 eye, ZVec3 center, ZVec3 up)
{
    ZVec3 n = (eye + center.negate()).normalize();
    ZVec3 u = (up.cross(n)).normalize();
    ZVec3 v = n.cross(u);
    
    float m[16] = {
        u.x, v.x, n.x, 0.0f,
        u.y, v.y, n.y, 0.0f,
        u.z, v.z, n.z, 0.0f,
        u.negate() * eye, v.negate() * eye, n.negate() * eye, 1.0f
    };
    
    return ZMatrix<4, 4>(m);
}


#pragma mark - Description

template <unsigned R, unsigned C>
std::string ZMatrixBase<R, C>::get_description()
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
template class ZMatrixBase<1, 1>;
template class ZMatrixBase<2, 2>;
template class ZMatrixBase<3, 3>;
template class ZMatrixBase<4, 4>;
template class ZMatrixBase<5, 5>;
template class ZMatrixBase<6, 6>;

} // namespace zge
