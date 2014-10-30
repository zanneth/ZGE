/*
 * types.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/29/2014
 */

#include "types.h"
#include <zge/util.h>

BEGIN_ZGE_NAMESPACE

#pragma mark - ZPoint2D

ZPoint2D::ZPoint2D(float x, float y) :
    x(x),
    y(y)
{}

std::vector<std::string> ZPoint2D::get_description_attributes() const
{
    return {
        ZUtil::format("{x = %f, y = %f}", x, y)
    };
}

#pragma mark - ZSize2D

ZSize2D::ZSize2D(float width, float height) :
    width(width),
    height(height)
{}

std::vector<std::string> ZSize2D::get_description_attributes() const
{
    return {
        ZUtil::format("{width = %f, height = %f}", width, height)
    };
}

#pragma mark - ZEdgeInsets

ZEdgeInsets::ZEdgeInsets(float top, float left, float bottom, float right) :
    top(top),
    left(left),
    bottom(bottom),
    right(right)
{}

std::vector<std::string> ZEdgeInsets::get_description_attributes() const
{
    return {
        ZUtil::format("{top = %f, left = %f, bottom = %f, right = %f}", top, left, bottom, right)
    };
}

#pragma mark - ZRect

ZRect::ZRect(const ZPoint2D &origin, const ZSize2D &size) :
    origin(origin),
    size(size)
{}

ZRect::ZRect(float x, float y, float width, float height) :
    origin(x, y),
    size(width, height)
{}

std::array<float, 4 * 2> ZRect::vertex_data() const
{
    std::array<float, 4 * 2> vertex_data{{
        origin.x, origin.y,
        origin.x + size.width, origin.y,
        origin.x, origin.y + size.height,
        origin.x + size.width, origin.y + size.height
    }};
    return vertex_data;
}

std::vector<std::string> ZRect::get_description_attributes() const
{
    return {
        origin.get_description_attributes()[0],
        size.get_description_attributes()[0]
    };
}

END_ZGE_NAMESPACE
