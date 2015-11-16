/*
 * shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#pragma once

#include <zge/foundation.h>
#include <zge/noncopyable.h>
#include <zge/types.h>
#include <functional>

ZGE_BEGIN_NAMESPACE

struct ZShaderCompilationResult {
    bool        success;
    std::string error;
};

struct ZShaderCallbacks {
    std::function<void(uint32_t)> destroy;
    std::function<void(uint32_t, const std::string&)> load_source;
    std::function<ZShaderCompilationResult(uint32_t)> compile;
};

class ZShader : ZNoncopyable {
public:
    virtual ~ZShader();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZShader);
    
    /// Loads shader source code from a file. Returns false on failure.
    bool load_source_file(const std::string path);
    
    /// Load shader source code from a string. Returns false on failure.
    bool load_source(const std::string source);
    
    /// Compiles the shader. Returns false on failure.
    bool compile();
    
    /// Returns the shader type.
    ZShaderType get_type() const;
    
    /// Returns the underlying handle for this shader.
    uint32_t get_handle() const;
    
    /// Returns true if source has been loaded into this shader.
    bool has_source() const;
    
    /// Returns true if the loaded source for this shader has been compiled.
    bool is_compiled() const;
    
protected:
    /// Only ZRenderContext may create shaders.
    ZShader(uint32_t handle, const ZShaderType &type, const ZShaderCallbacks &callbacks);
    friend class ZRenderContext;
    
private:
    std::string _load_and_preprocess_source_file(const std::string &path);
    void        _process_shader_source_line(const std::string &line, std::ostringstream &source_buffer);
    void        _handle_preprocessor_directive(const std::string &directive,
                                               const std::string &input,
                                               std::ostringstream &source_buffer);
    void        _include_directive_handler(const std::string &input, std::ostringstream &source_buffer);
    void        _version_directive_handler(const std::string &input, std::ostringstream &source_buffer);
    
private:
    uint32_t            _shader_handle;
    ZShaderCallbacks    _callbacks;
    ZShaderType         _type;
    std::string         _shader_source_path;
    bool                _has_source;
    bool                _compiled;
};

ZGE_DEFINE_SREF_TYPE(ZShader);

ZGE_END_NAMESPACE
