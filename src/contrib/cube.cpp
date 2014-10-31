/*
 * cube.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/13/2014
 */

#include "cube.h"

ZGE_BEGIN_NAMESPACE

static const float __cube_vertex_data[] = {
    // front
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,

    // right
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,

    // back
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    // left
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,

    // top
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,

    // bottom
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f
};

static const float __cube_normals_data[] = {
    // front
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    // right
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    // back
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    // left
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    // top
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    // bottom
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f
};

ZCube::ZCube(float scale) :
    _vertex_array(std::make_shared<ZVertexArray>()),
    _vbo(std::make_shared<ZGraphicsBuffer>()),
    _normals_vbo(std::make_shared<ZGraphicsBuffer>()),
    _scale(scale)
{
    const ZBufferUsage static_draw_usage = {ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW};
    
    // setup vbo
    ZBufferAttribute attr = {
        .components_per_vertex = 3,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    _vbo->add_attribute(attr);
    _vertex_array->add_buffer(_vbo, ZVERTEX_ATTRIB_POSITION);
    
    // copy vertex data to buffer, then scale all values
    size_t num_vertices = sizeof(__cube_vertex_data) / sizeof(__cube_vertex_data[0]);
    float vertex_data[num_vertices];
    std::copy(__cube_vertex_data, __cube_vertex_data + num_vertices, vertex_data);
    
    for (unsigned i = 0; i < num_vertices; ++i) {
        vertex_data[i] *= _scale;
    }
    
    _vbo->load_data(vertex_data, sizeof(vertex_data), static_draw_usage);
    
    // setup normals vbo
    ZBufferAttribute normal_attrib = {
        .components_per_vertex = 3,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    _normals_vbo->add_attribute(normal_attrib);
    _normals_vbo->load_data(__cube_normals_data, sizeof(__cube_normals_data), static_draw_usage);
    _vertex_array->add_buffer(_normals_vbo, ZVERTEX_ATTRIB_NORMAL);
}

#pragma mark - Accessors

float ZCube::get_scale() const { return _scale; }

#pragma mark - Overrides

ZGeometryRef ZCube::copy() const
{
    return std::make_shared<ZCube>(*this);
}

void ZCube::render(ZRenderContextRef context)
{
    ZGeometry::render(context);
    
    size_t num_triangles = sizeof(__cube_vertex_data) / sizeof(__cube_vertex_data[0]) / 3;
    context->draw_array(ZRENDER_MODE_TRIANGLES, _vertex_array, 0, num_triangles);
}

ZGE_END_NAMESPACE
