/*
 * cube.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/13/2014
 */

#pragma once

#include <zge/defines.h>
#include <zge/geometry.h>
#include <zge/types.h>

ZGE_BEGIN_NAMESPACE

class ZCube : public ZGeometry {
public:
    ZCube(float scale = 1.0f);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZCube);
    
    float get_scale() const;
    
    ZGeometryRef copy() const override;
    void render(ZRenderContextRef context) override;
    
private:
    ZVertexArrayRef    _vertex_array;
    ZGraphicsBufferRef _vbo;
    ZGraphicsBufferRef _normals_vbo;
    float              _scale;
};

ZGE_DEFINE_SREF_TYPE(ZCube);

ZGE_END_NAMESPACE
