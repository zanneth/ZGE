/*
 * geometry.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */

#include <zge/geometry.h>
#include <zge/logger.h>
#include <zge/util.h>

namespace zge {

ZMatrix ZGeometry::frustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tsb = top - bottom;
    float tab = top + bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    ZMatrix mat = {
        2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
        ral / rsl, tab / tsb, -fan / fsn, -1.0f,
        0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f
    };
    return mat;
}

ZMatrix ZGeometry::perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float fheight = std::tan(fovy / 360.0 * M_PI) * nearZ;
    float fwidth  = fheight * aspect;
    
    return frustum(-fwidth, fwidth, -fheight, fheight, nearZ, farZ);
}

ZMatrix ZGeometry::lookat(const ZVector &eye, const ZVector &center, const ZVector &up)
{
    ZVector n = (eye + -center).normalized();
    ZVector u = (up.cross(n)).normalized();
    ZVector v = n.cross(u);
    
    ZMatrix mat = {
        u[0], v[0], n[0], 0.0f,
        u[1], v[1], n[1], 0.0f,
        u[2], v[2], n[2], 0.0f,
        -u.dot(eye), -v.dot(eye), -n.dot(eye), 1.0f
    };
    return mat;
}

ZMatrix ZGeometry::ortho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    ZMatrix mat = {
        2.0f / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / tsb, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / fsn, 0.0f,
        -ral / rsl, -tab / tsb, -fan / fsn, 1.0f
    };
    return mat;
}

} // namespace zge
