/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/material.h>
#include <zge/render_context.h>
#include <memory>

namespace zge {

class ZGeometry {
public:
    ZGeometry();
    virtual ~ZGeometry();
    
    ZMaterialRef get_material() const;
    void set_material(ZMaterialRef material);
    
    virtual void render(ZRenderContextRef context);

protected:
    ZMaterialRef _material;
};

typedef std::shared_ptr<ZGeometry> ZGeometryRef;

} // namespace zge
