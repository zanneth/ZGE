/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */
 
#pragma once

namespace zge {

/** Shorthands **/
typedef Eigen::Vector2f ZVec2;
typedef Eigen::Vector3f ZVec3;
typedef Eigen::Vector4f ZVec4;
typedef Eigen::Matrix2f ZMat2;
typedef Eigen::Matrix3f ZMat3;
typedef Eigen::Matrix4f ZMat4;
typedef Eigen::AlignedBox2f ZRect;
typedef Eigen::Affine2f ZAffine2;
typedef Eigen::Affine3f ZAffine3;
typedef Eigen::AngleAxisf ZAngleAxis;
typedef Eigen::Quaternionf ZQuaternion;

const ZVec2 ZVec2Zero = ZVec2(0.0, 0.0);
const ZVec3 ZVec3Zero = ZVec3(0.0, 0.0, 0.0);

class ZGeometry {
public:
    static ZMat4 frustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    static ZMat4 perspective(float fovy, float aspect, float nearZ, float farZ);
    static ZMat4 lookat(const ZVec3 &eye, const ZVec3 &center, const ZVec3 &up);
};

} // namespace zge
