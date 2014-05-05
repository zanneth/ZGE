/*
 * quad.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/defines.h>
#include <zge/geometry.h>
#include <zge/types.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

class ZQuad : public ZGeometry {
    ZVertexArrayRef _vertex_array;
    ZRect           _quad_rect;
    
public:
    ZQuad(ZRect rect = {{0.0, 0.0}, {1.0, 1.0}});
    
    ZRect get_quad_rect() const;
    
    ZGeometryRef copy() const override;
    void render(ZRenderContextRef context) override;
};

typedef std::shared_ptr<ZQuad> ZQuadRef;

END_ZGE_NAMESPACE
