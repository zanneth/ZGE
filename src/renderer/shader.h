/*
 * shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#pragma once

#include <zge/foundation.h>
#include <zge/opengl.h>
#include <zge/noncopyable.h>
#include <zge/types.h>
#include <functional>

ZGE_BEGIN_NAMESPACE

class ZShader : ZNoncopyable {
public:
    ZShader(const ZShaderType &type);
    virtual ~ZShader();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZShader);
    
    // Loads shader source code from a file. Returns false on failure.
    bool load_source_file(const std::string path);
    
    // Load shader source code from a string. Returns false on failure.
    bool load_source(const std::string source);
    
    // Compiles the shader. Returns false on failure.
    bool compile();
    
    /* Accessors */
    ZShaderType get_type() const;
    bool has_source() const;
    bool is_compiled() const;
    
    /* Friends */
    friend class ZShaderProgram;

private:
    GLuint      _get_shader_handle() const;
    std::string _load_and_preprocess_source_file(const std::string &path);
    void        _process_shader_source_line(const std::string &line, std::ostringstream &source_buffer);
    void        _handle_preprocessor_directive(const std::string &directive,
                                               const std::string &input,
                                               std::ostringstream &source_buffer);
    void        _include_directive_handler(const std::string &input, std::ostringstream &source_buffer);
    
private:
    ZShaderType _type;
    GLuint _shader_handle;
    std::string _shader_source_path;
    bool _has_source;
    bool _compiled;
};

ZGE_DEFINE_SREF_TYPE(ZShader);

ZGE_END_NAMESPACE
