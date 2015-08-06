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

ZGE_BEGIN_NAMESPACE

ZGE_FORWARD_DECLARE_SREF(ZGeometry);

class ZGeometry {
public:
    ZGeometry() = default;
    ZGeometry(const ZGeometry &cp) = default;
    ZGeometry(ZGeometry &&mv) = default;
    virtual ~ZGeometry() = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZGeometry);
    
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

ZGE_DEFINE_SREF_TYPE(ZGeometry);

ZGE_END_NAMESPACE
