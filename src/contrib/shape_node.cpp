/*
 * shape_node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/17/2013
 */

#include <zge/shape_node.h>
#include <zge/logger.h>

namespace zge {

ZShapeNode::ZShapeNode(unsigned num_sides) :
    _num_sides(num_sides),
    _fill_color(ZWhiteColor),
    _vertex_array(new ZGLVertexArray)
{
    // debug
    _num_sides = 4;
    
    _size_info.vertex_buffer_sz = _num_sides * 2 * sizeof(float);
    _size_info.color_buffer_sz = _num_sides * 4 * sizeof(float);
    
    // allocate a VBO
    _vertex_array->bind();
    
    ZGLBufferRef vbo(new ZGLBuffer);
    vbo->set_target(GL_ARRAY_BUFFER);
    vbo->load_data(_size_info.vertex_buffer_sz + _size_info.color_buffer_sz, nullptr, GL_STATIC_DRAW);
    
    _vertex_array->add_buffer(vbo);
    
    // debug: generate normalized quad for this shape
    static float __quad_vertices[4 * 2] = {
        1.0, 1.0,
        0.0, 1.0,
        1.0, 0.0,
        0.0, 0.0
    };
    vbo->load_subdata(0, _size_info.vertex_buffer_sz, __quad_vertices);
    
    // setup attributes for the vertex data
    ZBufferAttribute vertex_attrib;
    vertex_attrib.index = ZVERTEX_ATTRIB_POSITION;
    vertex_attrib.components_per_vertex = 2;
    vertex_attrib.component_type = ZBUFFER_COMPONENT_TYPE_FLOAT;
    vertex_attrib.normalized = false;
    vertex_attrib.offset = 0;
    vertex_attrib.stride = 0;
    vbo->add_attribute(vertex_attrib);
    
    ZBufferAttribute color_attrib;
    color_attrib.index = ZVERTEX_ATTRIB_COLOR;
    color_attrib.components_per_vertex = 4;
    color_attrib.component_type = ZBUFFER_COMPONENT_TYPE_FLOAT;
    color_attrib.normalized = false;
    color_attrib.offset = _size_info.vertex_buffer_sz;
    color_attrib.stride = 0;
    vbo->add_attribute(color_attrib);
    
    _update_color_buffer();
}

ZShapeNode::~ZShapeNode()
{}

#pragma mark - Accessors

ZColor ZShapeNode::get_fill_color() const { return _fill_color; }

void ZShapeNode::set_fill_color(const ZColor &color)
{
    _fill_color = color;
    _update_color_buffer();
}

#pragma mark - Drawing

void ZShapeNode::draw(ZRenderContextRef context)
{
    _vertex_array->bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    _vertex_array->unbind();
}

#pragma mark - Private

void ZShapeNode::_update_color_buffer()
{
    ZGLBufferRef vbo = _vertex_array->get_buffers()[0];
    ZColor *vertex_color_data = new ZColor[_num_sides];
    for (unsigned i = 0; i < _num_sides; ++i) {
        vertex_color_data[i] = _fill_color;
    }
    vbo->load_subdata(_size_info.vertex_buffer_sz, _size_info.color_buffer_sz, vertex_color_data);
    delete[] vertex_color_data;
}

} // namespace zge
