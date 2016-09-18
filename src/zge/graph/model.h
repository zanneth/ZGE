/*
 * model.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */
 
#pragma once

#include <zge/core/defines.h>
#include <zge/graph/geometry.h>
#include <zge/renderer/graphics_buffer.h>
#include <zge/renderer/vertex_array.h>
#include <memory>
#include <string>

ZGE_BEGIN_NAMESPACE

class ZModel : public ZGeometry {
protected:
    std::string     _name;
    size_t          _faces_count;
    size_t          _vertices_count;
    ZVertexArrayRef _vertex_array;
    
    ZGraphicsBufferRef _vertex_vbo;
    ZGraphicsBufferRef _normal_vbo;
    
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
    std::string get_name() { return _name; }
    
    /* Geometry Overrides */
    void render(ZRenderContextRef context) override;
};

ZGE_DEFINE_SREF_TYPE(ZModel);

ZGE_END_NAMESPACE
