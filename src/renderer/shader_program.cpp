/*
 * shader_program.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/30/2012
 */
 
#include <zge/shader_program.h>
#include <zge/logger.h>

namespace zge {

ZShaderProgram::ZShaderProgram() :
    _linked(false)
{
    _program_handle = glCreateProgram();
}

ZShaderProgram::~ZShaderProgram()
{
    glDeleteProgram(_program_handle);
}

bool ZShaderProgram::attach_shader(ZShaderRef shader)
{
    bool success = false;
    
    if (shader != nullptr && shader->is_compiled()) {
        glAttachShader(_program_handle, shader->get_shader_handle());
        _shaders.push_back(shader);
        
        success = true;
    } else {
        ZLogger::log_error("Could not attach shader. Shader is invalid or not yet compiled.");
        success = false;
    }
    
    return success;
}

bool ZShaderProgram::detach_shader(ZShaderRef shader)
{
    bool success = false;
    
    if (shader != nullptr) {
        glDetachShader(_program_handle, shader->get_shader_handle());
        _shaders.erase(std::remove(_shaders.begin(), _shaders.end(), shader), _shaders.end());
        success = true;
    } else {
        ZLogger::log_error("Could not detach shader. Invalid shader object provided.");
    }
    
    return success;
}

bool ZShaderProgram::load_shader(const std::string &path, ZShaderType type)
{
    bool success = true;
    
    ZShaderRef shader = ZShaderRef(new ZShader(type));
    success &= shader->load_source_file(path);
    success &= shader->compile();
    success &= attach_shader(shader);
    
    return success;
}

bool ZShaderProgram::load_shader_source(const std::string &source, ZShaderType type)
{
    bool success = true;
    
    ZShaderRef shader = ZShaderRef(new ZShader(type));
    success &= shader->load_source(source);
    success &= shader->compile();
    success &= attach_shader(shader);
    
    return success;
}

bool ZShaderProgram::bind_attribute_index(ZVertexAttributeIndex attrib, std::string name)
{
    bool success = false;
    if (_attrib_map.find(attrib) == _attrib_map.end()) {
        glBindAttribLocation(_program_handle, attrib, name.c_str());
        _attrib_map[attrib] = name;
        success = true;
    }
    
    return success;
}

bool ZShaderProgram::link_program()
{
    GLint status = GL_FALSE;
    
    if (!_linked) {
        glLinkProgram(_program_handle);
        
        // log the error if there is one
        glGetProgramiv(_program_handle, GL_LINK_STATUS, &status);
        if (!status) {
            // print the error
            GLint errlen;
            glGetProgramiv(_program_handle, GL_INFO_LOG_LENGTH, &errlen);
            
            char *errstr = new char[errlen];
            glGetProgramInfoLog(_program_handle, errlen, 0, errstr);
            ZLogger::log_error(errstr);
            delete[] errstr;
            
            _linked = false;
        } else {
            _linked = true;
        }
    }
    
    return status == GL_TRUE;
}

bool ZShaderProgram::use_program()
{
    bool result = false;
    if (_linked && _program_handle != 0) {
        glUseProgram(_program_handle);
        result = true;
    }
    return result;
}

GLint ZShaderProgram::get_uniform(std::string name)
{
    GLint uniform = -1;
    
    if (_linked) {
        auto uniform_itr = _uniform_map.find(name);
        if (uniform_itr != _uniform_map.end()) {
            uniform = uniform_itr->second;
        } else {
            uniform = glGetUniformLocation(_program_handle, name.c_str());
            if (uniform != -1) {
                _uniform_map[name] = uniform;
            }
        }
    }
    
    return uniform;
}

} // namespace zge
