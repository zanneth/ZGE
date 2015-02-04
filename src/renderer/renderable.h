/*
 * renderable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/04/2015
 */

#pragma once

#include <zge/foundation.h>
#include <zge/render_context.h>

ZGE_BEGIN_NAMESPACE

class ZRenderable {
public:
    virtual ~ZRenderable() = default;
    virtual void render(ZRenderContextRef context) = 0;
};

ZGE_DEFINE_SREF_TYPE(ZRenderable);

ZGE_END_NAMESPACE
