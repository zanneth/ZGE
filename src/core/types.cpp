/*
 * types.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/29/2014
 */

#include "types.h"
#include "util.h"
#include <cmath>

ZGE_BEGIN_NAMESPACE

ZRect::ZRect(const ZPoint2D &origin, const ZSize2D &size) :
    origin(origin),
    size(size)
{}

ZRect::ZRect(float x, float y, float width, float height) :
    origin{x, y},
    size{width, height}
{}

ZPolar2D::ZPolar2D(float radius, float angle) :
    r(radius),
    theta(angle)
{}

ZPolar2D::ZPolar2D(const ZPoint2D &cartesian) :
    r(std::sqrt(cartesian.x * cartesian.x + cartesian.y * cartesian.y)),
    theta(std::atan(cartesian.y / cartesian.x))
{}

ZPoint2D ZPolar2D::cartesian() const
{
    return ZPoint2D{r * std::cos(theta), r * std::sin(theta)};
}

ZGE_END_NAMESPACE
