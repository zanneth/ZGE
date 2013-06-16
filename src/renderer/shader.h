/*
 * shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#pragma once

#include <memory>
#include <string>
#include <zge/gl_includes.h>
#include <zge/noncopyable.h>

namespace zge {

enum ZShaderType {
    ZVERTEX_SHADER,
    ZFRAGMENT_SHADER,
    ZGEOMETRY_SHADER
};

typedef std::shared_ptr<class ZShader> ZShaderRef;

class ZShader : ZNoncopyable {
protected:
    ZShaderType _type;
    GLuint _shader_handle;
    bool _has_source;
    bool _compiled;
    
public:
    ZShader(const ZShaderType &type);
    virtual ~ZShader();
    
    // Loads shader source code from a file. Returns false on failure.
    bool load_source_file(const std::string path);
    
    // Load shader source code from a string. Returns false on failure.
    bool load_source(const std::string source);
    
    // Compiles the shader. Returns false on failure.
    bool compile();
    
    /* Accessors */
    ZShaderType get_type() const;
    GLuint      get_shader_handle() const;
    
    bool has_source() const;
    bool is_compiled() const;
    
protected:
    static GLenum _get_opengl_shader_type(const ZShaderType &type);
};

} // namespace zge
