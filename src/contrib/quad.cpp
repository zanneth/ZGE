/*
 * quad.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#include <zge/quad.h>
#include <zge/graphics_buffer.h>

BEGIN_ZGE_NAMESPACE

ZQuad::ZQuad(ZRect rect) :
    _quad_rect(rect),
    _vertex_array(new ZVertexArray)
{
    ZGraphicsBufferRef vbo = ZGraphicsBufferRef(new ZGraphicsBuffer);
    ZBufferAttribute attr = {
        .components_per_vertex = 3,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    vbo->add_attribute(attr);
    
    float vertex_data[4 * 3] = {
        _quad_rect.origin.x, _quad_rect.origin.y, 0.0,
        _quad_rect.origin.x + _quad_rect.size.width, _quad_rect.origin.y, 0.0,
        _quad_rect.origin.x, _quad_rect.origin.y + _quad_rect.size.height, 0.0,
        _quad_rect.origin.x + _quad_rect.size.width, _quad_rect.origin.y + _quad_rect.size.height, 0.0
    };
    ZBufferUsage usage = {ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW};
    vbo->load_data(vertex_data, 4 * 3 * sizeof(float), usage);
    _vertex_array->add_buffer(vbo, ZVERTEX_ATTRIB_POSITION);
    
    ZGraphicsBufferRef texcoord_vbo = ZGraphicsBufferRef(new ZGraphicsBuffer);
    ZBufferAttribute texcoord_attr = {
        .components_per_vertex = 2,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    texcoord_vbo->add_attribute(texcoord_attr);
    
    float texcoord_data[4 * 2] = {
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0
    };
    texcoord_vbo->load_data(texcoord_data, 4 * 2 * sizeof(float), usage);
    _vertex_array->add_buffer(texcoord_vbo, ZVERTEX_ATTRIB_TEXCOORD0);
}

ZRect ZQuad::get_quad_rect() const
{
    return _quad_rect;
}

ZGeometryRef ZQuad::copy() const
{
    return ZQuadRef(new ZQuad(*this));
}

void ZQuad::render(ZRenderContextRef context)
{
    ZGeometry::render(context);
    context->draw_array(ZRENDER_MODE_TRIANGLE_STRIP, _vertex_array, 0, 4);
}

END_ZGE_NAMESPACE
