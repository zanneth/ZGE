/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */
 
#pragma once

#include <string>
#include <zge/matrix.h>
#include <zge/vector.h>

namespace zge {

struct ZPoint2D {
    float x;
    float y;
};

struct ZSize2D {
    float width;
    float height;
};

struct ZRect {
    ZPoint2D origin;
    ZSize2D size;
};

class ZGeometry {
public:
    // factory methods for specific types of matrices
    static ZMatrix frustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    static ZMatrix perspective(float fovy, float aspect, float nearZ, float farZ);
    static ZMatrix lookat(const ZVector &eye, const ZVector &center, const ZVector &up);
    static ZMatrix ortho(float left, float right, float bottom, float top, float nearZ, float farZ);
};

} // namespace zge
