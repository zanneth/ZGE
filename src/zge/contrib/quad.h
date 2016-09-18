/*
 * quad.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/core/defines.h>
#include <zge/graph/geometry.h>
#include <zge/core/types.h>
#include <memory>

ZGE_BEGIN_NAMESPACE

class ZQuad : public ZGeometry {
public:
    ZQuad(ZRect rect = {{0.0, 0.0}, {1.0, 1.0}});
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZQuad);
    
    ZRect get_quad_rect() const;
    void set_quad_rect(const ZRect &rect);
    
    ZRect get_texcoord_rect() const;
    void set_texcoord_rect(const ZRect &texcoord_rect);
    
    ZGeometryRef copy() const override;
    void render(ZRenderContextRef context) override;
    
private:
    ZVertexArrayRef    _vertex_array;
    ZGraphicsBufferRef _vbo;
    ZGraphicsBufferRef _texcoord_vbo;
    ZRect              _quad_rect;
    ZRect              _texcoord_rect;
};

ZGE_DEFINE_SREF_TYPE(ZQuad);

ZGE_END_NAMESPACE
