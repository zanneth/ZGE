/*
 * model.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */
 
#pragma once

#include <zge/core/defines.h>
#include <zge/core/types.h>
#include <zge/graph/geometry.h>
#include <zge/renderer/graphics_buffer.h>
#include <zge/renderer/vertex_array.h>
#include <memory>
#include <string>

ZGE_BEGIN_NAMESPACE

class ZModel : public ZGeometry {
public:
    ZModel(std::string filename = std::string());
    ZModel(const ZModel&) = default;
    ZModel(ZModel&&) = default;
    ~ZModel() = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZModel);
    
    ZGeometryRef copy() const override;
    
    /* Loading from 3DS Files */
    void load_file(std::string filename);
    
    /* Accessors */
    std::string get_name() const;
    
    // default is ZRENDER_MODE_TRIANGLE_STRIP
    ZRenderMode get_render_mode() const;
    void set_render_mode(ZRenderMode mode);
    
    /* Geometry Overrides */
    void render(ZRenderContextRef context) override;
    
protected:
    std::string         _name;
    ZRenderMode         _render_mode;
    size_t              _faces_count;
    size_t              _vertices_count;
    ZVertexArrayRef     _vertex_array;
    
    ZGraphicsBufferRef  _vertex_vbo;
    ZGraphicsBufferRef  _normal_vbo;
};

ZGE_DEFINE_SREF_TYPE(ZModel);

ZGE_END_NAMESPACE
