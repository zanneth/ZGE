/*
 * glyph.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/18/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/data.h>

ZGE_BEGIN_NAMESPACE

struct ZGlyph {
    char          character;
    ZSize2D       size;
    ZSize2D       advance;
    ZEdgeInsets   insets;
    ZDataConstRef bitmap;
};

ZGE_END_NAMESPACE
