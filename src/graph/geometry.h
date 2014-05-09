/*
 * geometry.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#pragma once

#include <zge/foundation.h>
#include <zge/material.h>
#include <zge/render_context.h>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZGeometry> ZGeometryRef;

class ZGeometry {
public:
    ZGeometry() = default;
    ZGeometry(const ZGeometry &cp) = default;
    ZGeometry(ZGeometry &&mv) = default;
    virtual ~ZGeometry() = default;
    
    virtual ZGeometryRef copy() const;
    
    std::vector<ZMaterialRef> get_materials() const;
    void add_material(ZMaterialRef material);
    void remove_material(ZMaterialRef material);
    void clear_materials();
    
    virtual void prepare_render(ZRenderContextRef context);
    virtual void render(ZRenderContextRef context);
    virtual void finalize_render(ZRenderContextRef context);

protected:
    std::vector<ZMaterialRef> _materials;
};

END_ZGE_NAMESPACE
