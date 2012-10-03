/*
 * geometry.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */

#include "zge/geometry.h"
#include "zge/logger.h"

    #include <iostream>
namespace zge {
namespace geometry {

ZMat4 frustum(float left, float right, float bottom, float top,
              float nearZ, float farZ)
{
    ZMat4 mat(ZMat4::Identity());
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    
    mat(0) = 2.0f * nearZ / deltaX;
    mat(1) = mat(2) = mat(3) = 0.0f;
    
    mat(4) = mat(6) = mat(7) = 0.0f;
    mat(5) = 2.0f * nearZ / deltaY;
    
    mat(8) = (right + left) / deltaX;
    mat(9) = (top + bottom) / deltaY;
    mat(10) = -(nearZ + farZ) / deltaZ;
    mat(11) = -1.0f;
    
    mat(12) = mat(14) = mat(15) = 0.0f;
    mat(14) = -2.0f * nearZ * farZ / deltaZ;
    
    return mat;
}

ZMat4 perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float fheight   = std::tan(fovy / 360.0 * M_PI) * nearZ;
    float fwidth    = fheight * aspect;
    
    return frustum(-fwidth, fwidth, -fheight, fheight, nearZ, farZ);
}

ZMat4 lookat(const ZVec3 &eye, const ZVec3 &center, const ZVec3 &up)
{
    ZVec3 n = (eye + -center).normalized();
    ZVec3 u = (up.cross(n)).normalized();
    ZVec3 v = n.cross(u);
    
    ZMat4 mat;
    mat <<
        u.x(), u.y(), u.z(), -u.dot(eye),
        v.x(), v.y(), v.z(), -v.dot(eye),
        n.x(), n.y(), n.z(), -n.dot(eye),
        0.0, 0.0, 0.0, 1.0;
    return mat;
}

} // namespace geometry
} // namespace zge
