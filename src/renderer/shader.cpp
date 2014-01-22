/*
 * shader.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include "shader.h"
#include <iostream>
#include <fstream>
#include <zge/exception.h>
#include <zge/logger.h>

namespace zge {

ZShader::ZShader(const ZShaderType &type) :
    _type(type),
    _has_source(false),
    _compiled(false)
{
    GLenum gltype = _get_opengl_shader_type(type);
    if (gltype != 0) {
        _shader_handle = glCreateShader(gltype);
    } else {
        ZException exception(ENGINE_EXCEPTION_CODE);
        exception.description = "Attempted to create a shader of an unsupported type.";
        throw exception;
    }
}

ZShader::~ZShader()
{
    glDeleteShader(_shader_handle);
}

#pragma mark - API

bool ZShader::load_source_file(const std::string path)
{
    bool success = false;
    std::string shader_src;
    
    // read the shader source from the filename
    std::ifstream file(path, std::ifstream::in);
    if (file) {
        std::string line;
        while (file.good()) {
            std::getline(file, line);
            shader_src += line + '\n';
        }
        
        // load source
        const char *shader_cstr = shader_src.c_str();
        glShaderSource(_shader_handle, 1, &shader_cstr, nullptr);
        
        success = true;
    } else {
        ZLogger::log_error("Shader source file %s does not exist.", path.c_str());
        success = false;
    }
    
    _has_source = success;
    return success;
}

bool ZShader::load_source(const std::string source)
{
    const char *shader_cstr = source.c_str();
    glShaderSource(_shader_handle, 1, &shader_cstr, nullptr);
    
    _has_source = true;
    return true;
}

bool ZShader::compile()
{
    if (!_has_source) {
        ZLogger::log_error("Could not compile shader. No source provided.");
        return false;
    }
    
    bool success = false;
    glCompileShader(_shader_handle);
    
    // check if there's an error and log it
    GLint status = GL_FALSE;
    glGetShaderiv(_shader_handle, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE) {
        success = true;
    } else {
        GLint errlen;
        glGetShaderiv(_shader_handle, GL_INFO_LOG_LENGTH, &errlen);
        
        char *errstr = new char[errlen];
        glGetShaderInfoLog(_shader_handle, errlen, 0, errstr);
        ZLogger::log_error(errstr);
        delete[] errstr;
        
        success = false;
    }
    
    _compiled = success;
    return success;
}

#pragma mark - Accessors

ZShaderType ZShader::get_type() const { return _type; }

bool ZShader::has_source() const { return _has_source; }

bool ZShader::is_compiled() const { return _compiled; }

#pragma mark - Private

GLuint ZShader::_get_shader_handle() const { return _shader_handle; }

#pragma mark - Internal

GLenum ZShader::_get_opengl_shader_type(const ZShaderType &type)
{
    GLenum gltype = 0;
    switch (type) {
        case ZVERTEX_SHADER:
            gltype = GL_VERTEX_SHADER;
            break;
        case ZFRAGMENT_SHADER:
            gltype = GL_FRAGMENT_SHADER;
            break;
        default:
            break;
    }
    return gltype;
}

} // namespace zge
