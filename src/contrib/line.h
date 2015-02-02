/*
 * line.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/02/2015
 */

#pragma once

#include <zge/foundation.h>
#include <zge/geometry.h>
#include <zge/vector.h>
#include <initializer_list>

ZGE_BEGIN_NAMESPACE

class ZLine : public ZGeometry {
public:
    ZLine(std::initializer_list<ZVector> points = {});
    ZLine(const std::vector<ZVector> points);
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZLine);
    
    void add_point(const ZVector &pt);
    void clear_points();
    
    ZGeometryRef copy() const override;
    void render(ZRenderContextRef context) override;
    
private:
    void _reload_vbo();
    
private:
    ZVertexArrayRef      _vertex_array;
    ZGraphicsBufferRef   _vbo;
    std::vector<ZVector> _points;
};

ZGE_DEFINE_SREF_TYPE(ZLine);

ZGE_END_NAMESPACE
