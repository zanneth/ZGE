/*
 * plane.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/05/2015
 */

#pragma once

#include <zge/foundation.h>
#include <zge/node.h>

ZGE_BEGIN_NAMESPACE

class ZPlane : public ZNode, ZNoncopyable {
public:
    ZPlane(const ZSize2D &size = {0.0, 0.0});
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZPlane);
    
    const ZSize2D& get_size() const;
    void           set_size(const ZSize2D &sz);
    
    const ZColor&  get_stroke_color() const;
    void           set_stroke_color(const ZColor &col);
    
    float          get_stroke_width() const;
    void           set_stroke_width(float w);
    
    const ZColor&  get_fill_color() const;
    void           set_fill_color(const ZColor &col);
    
private:
    void _reload_stroke();
    void _reload_fill();
    
private:
    ZSize2D  _size;
    ZColor   _strokecol;
    float    _stroke_width;
    ZColor   _fillcol;
    ZNodeRef _stroke_node;
    ZNodeRef _fill_node;
};

ZGE_DEFINE_SREF_TYPE(ZPlane);

ZGE_END_NAMESPACE
