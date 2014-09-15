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

BEGIN_ZGE_NAMESPACE

class ZCube : public ZGeometry {
public:
    ZCube(float scale = 1.0f);
    
    float get_scale() const;
    
    ZGeometryRef copy() const override;
    void render(ZRenderContextRef context) override;
    
private:
    ZVertexArrayRef    _vertex_array;
    ZGraphicsBufferRef _vbo;
    ZGraphicsBufferRef _normals_vbo;
    float              _scale;
};

typedef std::shared_ptr<ZCube> ZCubeRef;

END_ZGE_NAMESPACE
