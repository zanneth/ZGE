/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */
 
#pragma once

#include <Eigen/Eigen>
#include <string>

using namespace Eigen;

namespace zge {

const Vector2f Vector2fZero = { 0.f, 0.f };
const Vector3f ZVec3Zero = { 0.f, 0.f, 0.f };

class ZGeometry {
public:
    // factory methods for specific types of matrices
    static Matrix4f frustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    static Matrix4f perspective(float fovy, float aspect, float nearZ, float farZ);
    static Matrix4f lookat(const Vector3f &eye, const Vector3f &center, const Vector3f &up);
    static Matrix4f ortho(float left, float right, float bottom, float top, float nearZ, float farZ);

    // string representations of mathematical structures
    template <typename Derived>
    static std::string description(const MatrixBase<Derived> &matrix);
    static std::string description(const AlignedBox2f &rect);
};

} // namespace zge

#include <zge/geometry.hpp>
