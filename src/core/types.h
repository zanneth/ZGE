/*
 * types.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/20/2012
 */
 
#pragma once

#include <stdint.h>

namespace zge {

typedef uint32_t ZTimeInterval;

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
    
enum ZVertexAttributeIndex {
    ZVERTEX_ATTRIB_UNDEFINED = -1,
    ZVERTEX_ATTRIB_POSITION = 0,
    ZVERTEX_ATTRIB_COLOR,
    ZVERTEX_ATTRIB_NORMAL,
    ZVERTEX_ATTRIB_TEXCOORD0,
    ZVERTEX_ATTRIB_TEXCOORD1,
    ZVERTEX_ATTRIB_COUNT
};

} // namespace zge
