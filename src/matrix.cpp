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
ZMatrix<R, C>::ZMatrix()
{
    memset(matrix, 0, R * C * sizeof(GLfloat));
}

template <unsigned R, unsigned C>
ZMatrix<R, C>::ZMatrix(const ZMatrix &copy)
{
    for (unsigned i = 0; i < R * C; ++i) {
        matrix[i] = copy.matrix[i];
    }
}

template <unsigned R, unsigned C>
ZMatrix<R, C>::ZMatrix(GLfloat array[])
{
    for (unsigned i = 0; i < R * C; ++i) {
        matrix[i] = array[i];
    }
}


#pragma mark - Operators

template <unsigned R, unsigned C>
GLfloat ZMatrix<R, C>::operator[](int index)
{
    return matrix[index];
}

template <unsigned R, unsigned C>
ZMatrix<R, C> ZMatrix<R, C>::operator*(const ZMatrix<R, C> &other)
{
    if (R != C) {
        ZNotImplementedException e;
        e.extraInfo = "Only square matrices can be multiplied at the moment.";
        throw e;
    }
    
    unsigned n = R;
    ZMatrix<R, C> t;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            for (unsigned k = 0; k < n; ++k) {
                t.matrix[i * n + j] += matrix[i * n + k] * other.matrix[k * n + j];
            }
        }
    }
    
    return t;
}

template <unsigned R, unsigned C>
ZMatrix<R, C>& ZMatrix<R, C>::operator*=(const ZMatrix<R, C> &other)
{
    return (*this = (*this * other));
}


#pragma mark - Transforms

template <unsigned R, unsigned C>
ZMatrix<R, C> ZMatrix<R, C>::identity()
{
    if (R != C) {
        throw "Not a square matrix. Cannot create identity.";
    }
    
    ZMatrix<R, C> matrix;
    for (unsigned row = 0, col = 0; row < R && col < C; ++row, ++col) {
        matrix.matrix[row * C + col] = 1.0;
    }
    
    return matrix;
}

ZMatrix4 ZMatrix4::translation(float tx, float ty, float tz)
{
    ZMatrix4 mat = ZMatrix4::identity();
    mat.matrix[12] = tx;
    mat.matrix[13] = ty;
    mat.matrix[14] = tz;
    
    return mat;
}

ZMatrix4 ZMatrix4::rotation(float degrees, float x, float y, float z)
{
    float radians = ZUtil::degreesToRadians(degrees);
    
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
    
    return ZMatrix4(m);
}

ZMatrix4 ZMatrix4::scale(float sx, float sy, float sz)
{
    ZMatrix4 mat = ZMatrix4::identity();
    mat.matrix[0]   = sx;
    mat.matrix[5]   = sy;
    mat.matrix[10]  = sz;
    
    return mat;
}


#pragma mark - Geometry

ZMatrix4 ZMatrix4::frustum(float left, float right, float bottom, float top,
                           float nearZ, float farZ)
{
    ZMatrix4 mat = ZMatrix4::identity();
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    
    mat.matrix[0] = 2.0f * nearZ / deltaX;
    mat.matrix[1] = mat.matrix[2] = mat.matrix[3] = 0.0f;
    
    mat.matrix[4] = mat.matrix[6] = mat.matrix[7] = 0.0f;
    mat.matrix[5] = 2.0f * nearZ / deltaY;
    
    mat.matrix[8] = (right + left) / deltaX;
    mat.matrix[9] = (top + bottom) / deltaY;
    mat.matrix[10] = -(nearZ + farZ) / deltaZ;
    mat.matrix[11] = -1.0f;
    
    mat.matrix[12] = mat.matrix[14] = mat.matrix[15] = 0.0f;
    mat.matrix[14] = -2.0f * nearZ * farZ / deltaZ;
    
    return mat;
}

ZMatrix4 ZMatrix4::perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float fheight   = std::tan(fovy / 360.0 * M_PI) * nearZ;
    float fwidth    = fheight * aspect;
    
    ZMatrix4 frust = ZMatrix4::frustum(-fwidth, fwidth, -fheight, fheight, nearZ, farZ);
    return frust;
}

ZMatrix4 ZMatrix4::lookAt(ZVec3 eye, ZVec3 center, ZVec3 up)
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
    
    return ZMatrix4(m);
}


#pragma mark - Description

template <unsigned R, unsigned C>
std::string ZMatrix<R, C>::getDescription()
{
    std::ostringstream oss;
    for (unsigned i = 0; i < R * C; ++i) {
        if (i != 0 && i % C == 0) {
            oss << '\n';
        } else if (i != 0) {
            oss << '\t';
        }
        
        oss << matrix[i];
    }
    
    return oss.str();
}


// To avoid linker errors
template class ZMatrix<1, 1>;
template class ZMatrix<1, 2>;
template class ZMatrix<1, 3>;
template class ZMatrix<1, 4>;
template class ZMatrix<1, 5>;
template class ZMatrix<1, 6>;
template class ZMatrix<2, 1>;
template class ZMatrix<2, 2>;
template class ZMatrix<2, 3>;
template class ZMatrix<2, 4>;
template class ZMatrix<2, 5>;
template class ZMatrix<2, 6>;
template class ZMatrix<3, 1>;
template class ZMatrix<3, 2>;
template class ZMatrix<3, 3>;
template class ZMatrix<3, 4>;
template class ZMatrix<3, 5>;
template class ZMatrix<3, 6>;
template class ZMatrix<4, 1>;
template class ZMatrix<4, 2>;
template class ZMatrix<4, 3>;
template class ZMatrix<4, 4>;
template class ZMatrix<4, 5>;
template class ZMatrix<4, 6>;
template class ZMatrix<5, 1>;
template class ZMatrix<5, 2>;
template class ZMatrix<5, 3>;
template class ZMatrix<5, 4>;
template class ZMatrix<5, 5>;
template class ZMatrix<5, 6>;
template class ZMatrix<6, 1>;
template class ZMatrix<6, 2>;
template class ZMatrix<6, 3>;
template class ZMatrix<6, 4>;
template class ZMatrix<6, 5>;
template class ZMatrix<6, 6>;

} // namespace zge
