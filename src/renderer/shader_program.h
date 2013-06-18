/*
 * shader_program.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/30/2012
 */
 
#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <zge/opengl.h>
#include <zge/shader.h>

namespace zge {

enum ZVertexAttribute {
    ZVERTEX_ATTRIB_POSITION,
    ZVERTEX_ATTRIB_NORMAL,
    ZVERTEX_ATTRIB_COLOR,
    ZVERTEX_ATTRIB_TEXCOORD0,
    ZVERTEX_ATTRIB_TEXCOORD1,
    ZVERTEX_ATTRIB_COUNT
};

typedef std::shared_ptr<class ZShaderProgram> ZShaderProgramRef;

class ZShaderProgram {
protected:
    GLuint _program_handle;
    std::vector<ZShaderRef> _shaders;
    std::map<GLuint, std::string> _attrib_map;
    std::map<std::string, GLint> _uniform_map;
    bool _linked;
    
public:
    ZShaderProgram();
    ZShaderProgram(const ZShaderProgram&) = delete;
    ~ZShaderProgram();
    
    GLuint get_program_handle() const { return _program_handle; }
    std::vector<ZShaderRef> get_attached_shaders() const { return _shaders; }
    bool is_linked() const { return _linked; }
    
    bool attach_shader(ZShaderRef shader);
    bool detach_shader(ZShaderRef shader);
    bool load_shader(const std::string &path, ZShaderType type); // convenience -- compiles and attaches a shader
    bool load_shader_source(const std::string &source, ZShaderType type); // convenience (as above)
    
    bool bind_attribute(ZVertexAttribute attrib, std::string name);
    bool link_program();
    bool use_program();
    
    GLint get_uniform(std::string name);
};

} // namespace zge