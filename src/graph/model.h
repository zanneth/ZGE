/*
 * model.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/geometry.h>
#include <zge/graphics_buffer.h>
#include <zge/vertex_array.h>
#include <memory>
#include <string>

BEGIN_ZGE_NAMESPACE

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
    
    ZGeometryRef copy() const override;
    
    /* Loading from 3DS Files */
    void load_file(std::string filename);
    
    /* Accessors */
    std::string get_name() { return _name; }
    
    /* Geometry Overrides */
    void render(ZRenderContextRef context) override;
};

typedef std::shared_ptr<ZModel> ZModelRef;

END_ZGE_NAMESPACE
