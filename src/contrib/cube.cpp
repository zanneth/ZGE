/*
 * cube.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/13/2014
 */

#include "cube.h"

BEGIN_ZGE_NAMESPACE

static const float __cube_vertex_data[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};

ZCube::ZCube(float scale) :
    _vertex_array(std::make_shared<ZVertexArray>()),
    _vbo(std::make_shared<ZGraphicsBuffer>()),
    _scale(scale)
{
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
    
    ZBufferUsage usage = {ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW};
    _vbo->load_data(vertex_data, sizeof(vertex_data), usage);
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
    
    size_t num_faces = sizeof(__cube_vertex_data) / sizeof(__cube_vertex_data[0]) / 3;
    context->draw_array(ZRENDER_MODE_TRIANGLE_STRIP, _vertex_array, 0, num_faces);
}

END_ZGE_NAMESPACE
