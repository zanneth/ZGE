/*
 * plane.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/05/2015
 */

#include "plane.h"
#include "geometry.h"
#include "graphics_buffer.h"
#include "quad.h"
#include "vertex_array.h"
#include <array>

ZGE_BEGIN_NAMESPACE

class ZStrokeGeometry : public ZGeometry {
public:
    ZStrokeGeometry(const ZSize2D &bounds_sz, float stroke_w) :
        _bounds_sz(bounds_sz),
        _stroke_w(stroke_w)
    {
        ZRenderContext *ctx = ZRenderContext::get_current_context();
        zassert(ctx, "invalid context");
        
        _varray = ctx->create_vertex_array();
        _vbo = ctx->create_graphics_buffer();
        
        ZBufferAttribute attr = {
            .components_per_vertex = 3,
            .component_type = ZCOMPONENT_TYPE_FLOAT,
            .normalized = false,
            .stride = 0,
            .offset = 0
        };
        _vbo->add_attribute(attr);
        _varray->add_buffer(_vbo, ZVERTEX_ATTRIB_POSITION);
        
        const ZRect bottomq = {{0.0, 0.0}, {bounds_sz.width, stroke_w}};
        const ZRect leftq = {{0.0, 0.0}, {stroke_w, bounds_sz.height}};
        const ZRect rightq = {{bounds_sz.width - stroke_w, 0.0}, {stroke_w, bounds_sz.height}};
        const ZRect topq = {{0.0, bounds_sz.height - stroke_w}, {bounds_sz.width, stroke_w}};
        const ZRect quads[4] = {bottomq, leftq, rightq, topq};
        
        std::array<float, 4*4*3> vertex_data;
        unsigned data_idx = 0;
        
        for (unsigned i = 0; i < 4; ++i) {
            const ZRect quadr = quads[i];
            const std::array<float, 4*3> quad_vdata = _create_quad_vertex_data(quadr);
            for (const float &cmp : quad_vdata) {
                vertex_data[data_idx++] = cmp;
            }
        }
        
        ZBufferUsage usage = {ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW};
        _vbo->load_data(vertex_data.data(), 4 * 4 * 3 * sizeof(float), usage);
    }
    
    const ZSize2D& get_bounds_size() const
    {
        return _bounds_sz;
    }
    
    ZGeometryRef copy() const override
    {
        return ZStrokeGeometry::create(*this);
    }
    
    void render(ZRenderContextRef context) override
    {
        ZGeometry::render(context);
        context->draw_array(ZRENDER_MODE_TRIANGLE_STRIP, _varray, 0, 4 * 4);
    }
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZStrokeGeometry);
    
private:
    static std::array<float, 4*3> _create_quad_vertex_data(const ZRect &rect)
    {
        std::array<float, 4*3> vertex_data = {{
            rect.origin.x + rect.size.width, rect.origin.y, 0.0,
            rect.origin.x, rect.origin.y, 0.0,
            rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, 0.0,
            rect.origin.x, rect.origin.y + rect.size.height, 0.0,
        }};
        return vertex_data;
    }
    
private:
    ZSize2D            _bounds_sz;
    float              _stroke_w;
    ZVertexArrayRef    _varray;
    ZGraphicsBufferRef _vbo;
};

ZGE_DEFINE_SREF_TYPE(ZStrokeGeometry);

// -----------------------------------------------------------------------------

ZPlane::ZPlane(const ZSize2D &size) :
    _size(size),
    _strokecol(ZColor::white),
    _stroke_width(1.0),
    _fillcol(ZColor::white),
    _stroke_node(ZNode::create()),
    _fill_node(ZNode::create())
{
    _reload_stroke();
    _reload_fill();
    
    add_child(_stroke_node);
    add_child(_fill_node);
}

#pragma mark - Accessors

const ZSize2D& ZPlane::get_size() const { return _size; }
const ZColor& ZPlane::get_stroke_color() const { return _strokecol; }
float ZPlane::get_stroke_width() const { return _stroke_width; }
const ZColor& ZPlane::get_fill_color() const { return _fillcol; }

void ZPlane::set_size(const ZSize2D &sz)
{
    _size = sz;
    _reload_stroke();
    _reload_fill();
}

void ZPlane::set_stroke_color(const ZColor &col)
{
    _strokecol = col;
    _reload_stroke();
}

void ZPlane::set_stroke_width(float w)
{
    _stroke_width = w;
    _reload_stroke();
    _reload_fill();
}

void ZPlane::set_fill_color(const ZColor &col)
{
    _fillcol = col;
    _reload_fill();
}

#pragma mark - Internal

void ZPlane::_reload_stroke()
{
    ZColorMaterialRef mat = ZColorMaterial::create(_strokecol);
    ZStrokeGeometryRef stroke_geom = ZStrokeGeometry::create(_size, _stroke_width);
    stroke_geom->add_material(mat);
    
    _stroke_node->set_geometry(stroke_geom);
}

void ZPlane::_reload_fill()
{
    ZColorMaterialRef mat = ZColorMaterial::create(_fillcol);
    ZRect fillrect = {
        {_stroke_width, _stroke_width},
        {_size.width - _stroke_width * 2.0f, _size.height - _stroke_width * 2.0f}
    };
    ZQuadRef fill_geom = ZQuad::create(fillrect);
    fill_geom->add_material(mat);
    
    _fill_node->set_geometry(fill_geom);
}

ZGE_END_NAMESPACE
