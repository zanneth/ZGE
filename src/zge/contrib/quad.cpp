/*
 * quad.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#include <zge/contrib/quad.h>
#include <zge/renderer/graphics_buffer.h>
#include <zge/renderer/render_context.h>

ZGE_BEGIN_NAMESPACE

ZQuad::ZQuad(ZRect rect) :
    _quad_rect(rect),
    _texcoord_rect({{0.0, 0.0}, {1.0, 1.0}})
{
    ZRenderContext *ctx = ZRenderContext::get_current_context();
    zassert(ctx, "invalid context");
    
    _vertex_array = ctx->create_vertex_array();
    _vbo = ctx->create_graphics_buffer();
    _texcoord_vbo = ctx->create_graphics_buffer();
    
    ZBufferAttribute attr = {
        .components_per_vertex = 3,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    _vbo->add_attribute(attr);
    set_quad_rect(rect);
    _vertex_array->add_buffer(_vbo, ZVERTEX_ATTRIB_POSITION);
    
    ZBufferAttribute texcoord_attr = {
        .components_per_vertex = 2,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    _texcoord_vbo->add_attribute(texcoord_attr);
    set_texcoord_rect(_texcoord_rect);
    _vertex_array->add_buffer(_texcoord_vbo, ZVERTEX_ATTRIB_TEXCOORD0);
}

ZRect ZQuad::get_quad_rect() const
{
    return _quad_rect;
}

void ZQuad::set_quad_rect(const ZRect &rect)
{
    _quad_rect = rect;
    
    float vertex_data[4 * 3] = {
        rect.origin.x + rect.size.width, rect.origin.y, 0.0,
        rect.origin.x, rect.origin.y, 0.0,
        rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, 0.0,
        rect.origin.x, rect.origin.y + rect.size.height, 0.0,
    };
    ZBufferUsage usage = {ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW};
    _vbo->load_data(vertex_data, 4 * 3 * sizeof(float), usage);
}

ZRect ZQuad::get_texcoord_rect() const
{
    return _texcoord_rect;
}

void ZQuad::set_texcoord_rect(const ZRect &texcoord_rect)
{
    _texcoord_rect = texcoord_rect;
    
    float texcoord_data[4 * 2] = {
        texcoord_rect.origin.x + texcoord_rect.size.width, texcoord_rect.origin.y,
        texcoord_rect.origin.x, texcoord_rect.origin.y,
        texcoord_rect.origin.x + texcoord_rect.size.width, texcoord_rect.origin.y + texcoord_rect.size.height,
        texcoord_rect.origin.x, texcoord_rect.origin.y + texcoord_rect.size.height,
    };
    ZBufferUsage usage = {ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW};
    _texcoord_vbo->load_data(texcoord_data, 4 * 2 * sizeof(float), usage);
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

ZGE_END_NAMESPACE
