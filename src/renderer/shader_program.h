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
#include <zge/defines.h>
#include <zge/shader.h>
#include <zge/types.h>
#include <zge/uniform.h>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZShaderProgram> ZShaderProgramRef;

class ZShaderProgram : public std::enable_shared_from_this<ZShaderProgram> {
protected:
    GLuint _program_handle;
    std::vector<ZShaderRef> _shaders;
    std::map<GLuint, std::string> _attrib_map;
    std::map<std::string, ZUniformRef> _uniform_map;
    bool _linked;
    bool _uniforms_loaded;
    
public:
    ZShaderProgram();
    ZShaderProgram(const ZShaderProgram&) = delete;
    ~ZShaderProgram();
    
    std::vector<ZShaderRef> get_attached_shaders() const { return _shaders; }
    bool is_linked() const { return _linked; }
    
    bool attach_shader(ZShaderRef shader);
    bool detach_shader(ZShaderRef shader);
    bool load_shader(const std::string &path, ZShaderType type); // convenience -- compiles and attaches a shader
    bool load_shader_source(const std::string &source, ZShaderType type); // convenience (as above)
    
    bool bind_attribute_index(ZVertexAttributeIndex attrib, std::string name);
    bool link_program();
    bool use_program();
    
    ZUniformRef get_uniform(std::string name);

private:
    void _load_uniforms();
    void _uniform_modified(ZUniformRef uniform);
};

END_ZGE_NAMESPACE
