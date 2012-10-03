/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */
 
#pragma once

namespace zge {

typedef Eigen::Vector2f ZVec2;
typedef Eigen::Vector3f ZVec3;
typedef Eigen::Vector4f ZVec4;
typedef Eigen::Matrix2f ZMat2;
typedef Eigen::Matrix3f ZMat3;
typedef Eigen::Matrix4f ZMat4;
typedef Eigen::Affine2f ZAffine2;
typedef Eigen::Affine3f ZAffine3;

namespace geometry {

ZMat4 frustum(float left, float right, float bottom, float top,
              float nearZ, float farZ);
ZMat4 perspective(float fovy, float aspect, float nearZ, float farZ);
ZMat4 lookat(const ZVec3 &eye, const ZVec3 &center, const ZVec3 &up);

} // namespace geometry
} // namespace zge
