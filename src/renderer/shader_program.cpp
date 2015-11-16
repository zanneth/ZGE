/*
 * shader_program.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/30/2012
 */
 
#include <zge/shader_program.h>
#include <zge/exception.h>
#include <zge/logger.h>
#include <zge/render_context.h>
#include <zge/util.h>

ZGE_BEGIN_NAMESPACE

ZShaderProgram::ZShaderProgram(uint32_t handle, const ZShaderProgramCallbacks &callbacks) :
    _program_handle(handle),
    _callbacks(callbacks),
    _linked(false)
{}

ZShaderProgram::~ZShaderProgram()
{
    _callbacks.destroy(_program_handle);
}

#pragma mark - Accessors

uint32_t ZShaderProgram::get_program_handle() const
{
    return _program_handle;
}

std::vector<ZShaderRef> ZShaderProgram::get_attached_shaders() const
{
    return _shaders;
}

bool ZShaderProgram::is_linked() const
{
    return _linked;
}

#pragma mark - API

bool ZShaderProgram::attach_shader(ZShaderRef shader)
{
    bool success = false;
    
    if (shader != nullptr && shader->is_compiled()) {
        _callbacks.attach(_program_handle, shader->get_handle());
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
        _callbacks.detach(_program_handle, shader->get_handle());
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
    
    ZRenderContext *ctx = ZRenderContext::get_current_context();
    zassert(ctx, "invalid context");
    
    ZShaderRef shader = ctx->create_shader(type);
    success &= shader->load_source_file(path);
    success &= shader->compile();
    success &= attach_shader(shader);
    
    return success;
}

bool ZShaderProgram::load_shader_source(const std::string &source, ZShaderType type)
{
    bool success = true;
    
    ZRenderContext *ctx = ZRenderContext::get_current_context();
    zassert(ctx, "invalid context");
    
    ZShaderRef shader = ctx->create_shader(type);
    success &= shader->load_source(source);
    success &= shader->compile();
    success &= attach_shader(shader);
    
    return success;
}

void ZShaderProgram::bind_attribute_index(ZVertexAttributeIndex attrib, std::string name)
{
    _attrib_map[attrib] = name;
}

const std::map<uint32_t, std::string>& ZShaderProgram::get_bound_attributes() const
{
    return _attrib_map;
}

bool ZShaderProgram::link_program()
{
    if (!_linked) {
        ZShaderProgramLinkResult result = _callbacks.link(_program_handle, _attrib_map);
        if (result.success) {
            for (ZUniformRef uniform : result.uniforms) {
                const std::string name = uniform->get_name();
                _uniform_map[name] = uniform;
            }
        } else {
            ZLogger::log_error("SHADER PROGRAM LINK ERROR: %s", result.error.c_str());
        }
        
        _linked = result.success;
    }
    
    return _linked;
}

ZUniformRef ZShaderProgram::get_uniform(std::string name) const
{
    ZUniformRef uniform = nullptr;
    
    if (_linked) {
        auto uniform_itr = _uniform_map.find(name);
        if (uniform_itr != _uniform_map.end()) {
            uniform = uniform_itr->second;
        }
    }
    
    return uniform;
}

std::vector<ZUniformRef> ZShaderProgram::get_dirty_uniforms() const
{
    std::vector<ZUniformRef> dirty_uniforms;
    for (const auto &uniform_pair : _uniform_map) {
        if (uniform_pair.second->is_dirty()) {
            dirty_uniforms.push_back(uniform_pair.second);
        }
    }
    return dirty_uniforms;
}

ZGE_END_NAMESPACE
