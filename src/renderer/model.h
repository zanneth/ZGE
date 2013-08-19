/*
 * model.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */
 
#pragma once

#include <zge/gl_buffer.h>
#include <zge/gl_vertexarray.h>
#include <memory>
#include <string>

namespace zge {

typedef std::shared_ptr<class ZModel> ZModelRef;

class ZModel {
protected:
    std::string     _name;
    unsigned        _num_faces;
    unsigned        _num_vertices;
    ZGLVertexArrayRef _vertex_array;
    ZGLBufferRef    _element_vbo;
    ZGLBufferRef    _vertex_vbo;
    ZGLBufferRef    _normal_vbo;
    
public:
    ZModel(std::string filename = std::string());
    ZModel(const ZModel&) = default;
    
    /* Loading from 3DS Files */
    void load_file(std::string filename);
    
    /* Accessors */
    std::string get_name() { return _name; }
    
    /* Drawing */
    void draw();
};

} // namespace zge
