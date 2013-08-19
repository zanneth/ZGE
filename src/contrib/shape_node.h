/*
 * shape_node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/17/2013
 */

#pragma once

#include <zge/color.h>
#include <zge/gl_buffer.h>
#include <zge/gl_vertexarray.h>
#include <zge/node.h>
#include <zge/render_context.h>

namespace zge {

class ZShapeNode : public ZNode {
    unsigned     _num_sides;
    ZColor       _fill_color;
    ZGLVertexArrayRef _vertex_array;
    struct {
        size_t vertex_buffer_sz;
        size_t color_buffer_sz;
    } _size_info;
    
public:
    ZShapeNode(unsigned num_sides = 4);
    virtual ~ZShapeNode();
    
    ZColor  get_fill_color() const;
    void    set_fill_color(const ZColor &color);
    
    void draw(ZRenderContextRef context) override;

private:
    void _update_color_buffer();
};
    
} // namespace zge
