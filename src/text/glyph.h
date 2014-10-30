/*
 * glyph.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/18/2014
 */

#pragma once

#include <zge/foundation.h>
#include <zge/data.h>

BEGIN_ZGE_NAMESPACE

struct ZGlyph {
    ZSize2D     size;
    ZSize2D     advance;
    ZEdgeInsets insets;
    ZDataRef    bitmap;
};

END_ZGE_NAMESPACE
