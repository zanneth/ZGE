/*
 * types.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/29/2014
 */

#include "types.h"
#include <zge/util.h>

ZGE_BEGIN_NAMESPACE

ZRect::ZRect(const ZPoint2D &origin, const ZSize2D &size) :
    origin(origin),
    size(size)
{}

ZRect::ZRect(float x, float y, float width, float height) :
    origin{x, y},
    size{width, height}
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

ZGE_END_NAMESPACE
