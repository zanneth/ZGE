/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/render_context.h>
#include <memory>

namespace zge {

class ZGeometry {
public:
    ZGeometry();
    virtual ~ZGeometry();
    
    virtual void render(ZRenderContextRef context) = 0;
};

typedef std::shared_ptr<ZGeometry> ZGeometryRef;

} // namespace zge
