/*
 * model.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */
 
#pragma once

#include <memory>
#include <string>

#include "zge/gl_includes.h"

namespace zge {

typedef std::shared_ptr<class ZModel> ZModelRef;

class ZModel {
protected:
    std::string _name;
    unsigned    _num_faces;
    unsigned    _num_vertices;
    GLuint      _element_vbo;
    GLuint      _vertex_vbo;
    GLuint      _normal_vbo;
    
public:
    ZModel(std::string filename = std::string());
    ZModel(const ZModel&);
    ZModel(const ZModel&&);
    ZModel& operator=(const ZModel&);
    ZModel& operator=(const ZModel&&);
    virtual ~ZModel();
    
    /** Loading from 3DS Files **/
    void load_file(std::string filename);
    
    /** Accessors **/
    std::string get_name() { return _name; }
    
    /** Drawing **/
    void draw();
    
private:
    void _check_buffers();
};

} // namespace zge
