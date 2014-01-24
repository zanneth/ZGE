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

typedef std::shared_ptr<class ZGeometry> ZGeometryRef;

class ZGeometry {
public:
    ZGeometry();
    ZGeometry(const ZGeometry &cp);
    ZGeometry(ZGeometry &&mv);
    virtual ~ZGeometry();
    
    virtual ZGeometryRef copy() const;
    
    ZMaterialRef get_material() const;
    void set_material(ZMaterialRef material);
    
    virtual void render(ZRenderContextRef context);

protected:
    ZMaterialRef _material;
};

} // namespace zge
