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

ZGE_BEGIN_NAMESPACE

struct ZShaderProgramLinkResult {
    bool success;
    std::string error;
    std::vector<ZUniformRef> uniforms;
};

struct ZShaderProgramCallbacks {
    std::function<void(uint32_t)> destroy;
    std::function<void(uint32_t, uint32_t)> attach;
    std::function<void(uint32_t, uint32_t)> detach;
    std::function<ZShaderProgramLinkResult(uint32_t, std::map<uint32_t, std::string>)> link;
};

class ZShaderProgram : ZNoncopyable {
public:
    virtual ~ZShaderProgram();
    
    /// Returns the underlying handle for this program object.
    uint32_t get_program_handle() const;
    
    /// Returns an array of all attached shaders.
    std::vector<ZShaderRef> get_attached_shaders() const;
    
    /// Returns true if the program has been linked by the graphics subsystem.
    bool is_linked() const;
    
    /// Attach a shader to this program.
    bool attach_shader(ZShaderRef shader);
    
    /// Detach a previously attached shader.
    bool detach_shader(ZShaderRef shader);
    
    /// Convenience: creates a new shader and attaches it to this program.
    bool load_shader(const std::string &path, ZShaderType type);
    
    /// Convenience: creates a new shader and attaches it to this program.
    bool load_shader_source(const std::string &source, ZShaderType type);
    
    /// Enable a vertex attribute to be used by this program.
    void bind_attribute_index(ZVertexAttributeIndex attrib, std::string name);
    
    /// Returns all bound attributes for this program.
    const std::map<uint32_t, std::string>& get_bound_attributes() const;
    
    /// Link the program in the graphics subsystem.
    bool link_program();
    
    /// Returns a uniform object with the specified name.
    ZUniformRef get_uniform(std::string name) const;
    
    /// Returns an array of all dirty uniforms.
    std::vector<ZUniformRef> get_dirty_uniforms() const;
    
protected:
    /// Only ZRenderContext may create shader programs.
    ZShaderProgram(uint32_t handle, const ZShaderProgramCallbacks &callbacks);
    friend class ZRenderContext;

protected:
    uint32_t                            _program_handle;
    ZShaderProgramCallbacks             _callbacks;
    std::vector<ZShaderRef>             _shaders;
    std::map<uint32_t, std::string>     _attrib_map;
    std::map<std::string, ZUniformRef>  _uniform_map;
    bool                                _linked;
};

ZGE_DEFINE_SREF_TYPE(ZShaderProgram);

ZGE_END_NAMESPACE
