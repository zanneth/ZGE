/*
 * line.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/02/2015
 */

#include "line.h"

ZGE_BEGIN_NAMESPACE

ZLine::ZLine(std::initializer_list<ZVector> points) :
    ZLine(std::vector<ZVector>(points))
{}

ZLine::ZLine(const std::vector<ZVector> points) :
    _vertex_array(ZVertexArray::create()),
    _vbo(ZGraphicsBuffer::create()),
    _points(points)
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
    
    _reload_vbo();
}

void ZLine::add_point(const ZVector &pt)
{
    _points.push_back(pt);
    _reload_vbo();
}

void ZLine::add_points(const std::vector<ZVector> &pts)
{
    _points.insert(_points.end(), pts.begin(), pts.end());
    _reload_vbo();
}

void ZLine::clear_points()
{
    _points.clear();
    _reload_vbo();
}

#pragma mark - Overrides

ZGeometryRef ZLine::copy() const
{
    return ZLine::create(*this);
}

void ZLine::render(ZRenderContextRef context)
{
    ZGeometry::render(context);
    context->draw_array(ZRENDER_MODE_LINE_STRIP, _vertex_array, 0, _points.size());
}

#pragma mark - Internal

void ZLine::_reload_vbo()
{
    std::vector<float> vertex_data;
    for (ZVector pt : _points) {
        const float *pt_data = pt.get_data();
        std::copy(pt_data, pt_data + 3, std::back_inserter(vertex_data));
    }
    
    ZBufferUsage usage = {ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW};
    _vbo->load_data(vertex_data.data(), vertex_data.size() * sizeof(float), usage);
}

ZGE_END_NAMESPACE
