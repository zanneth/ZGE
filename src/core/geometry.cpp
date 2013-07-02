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

Matrix4f ZGeometry::frustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    Matrix4f mat(Matrix4f::Identity());
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

Matrix4f ZGeometry::perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float fheight = std::tan(fovy / 360.0 * M_PI) * nearZ;
    float fwidth  = fheight * aspect;
    
    return frustum(-fwidth, fwidth, -fheight, fheight, nearZ, farZ);
}

Matrix4f ZGeometry::lookat(const Vector3f &eye, const Vector3f &center, const Vector3f &up)
{
    Vector3f n = (eye + -center).normalized();
    Vector3f u = (up.cross(n)).normalized();
    Vector3f v = n.cross(u);
    
    Matrix4f mat;
    mat <<
        u.x(), u.y(), u.z(), -u.dot(eye),
        v.x(), v.y(), v.z(), -v.dot(eye),
        n.x(), n.y(), n.z(), -n.dot(eye),
        0.0, 0.0, 0.0, 1.0;
    return mat;
}

Matrix4f ZGeometry::ortho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    Matrix4f mat;
    mat <<
        2.0f / rsl, 0.0f, 0.0f, -ral / rsl,
        0.0f, 2.0f / tsb, 0.0f, -tab / tsb,
        0.0f, 0.0f, -2.0f / fsn, -fan / fsn,
        0.0f, 0.0f, 0.0f, 1.0f;
    
    return mat;
}

std::string ZGeometry::description(const AlignedBox2f &rect)
{
    return ZUtil::format("{%s, %s}", description(rect.min()).c_str(), description(rect.max()).c_str());
}

} // namespace zge
