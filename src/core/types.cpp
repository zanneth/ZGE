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

ZGE_END_NAMESPACE
