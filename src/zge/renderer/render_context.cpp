/*
 * render_context.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <zge/renderer/render_context.h>
#include <zge/renderer/opengl.h>
#include <zge/util/glutil.h>
#include <zge/renderer/light.h>
#include <zge/util/logger.h>
#include <zge/core/resource_bundle.h>
#include <zge/renderer/uniform.h>
#include <zge/util/util.h>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <vector>

ZGE_BEGIN_NAMESPACE

struct ZLightUniformDescriptor {
    std::string position_name;
    std::string color_name;
    std::string exists_name;
    
    static const std::string base_position_name;
    static const std::string base_color_name;
    static const std::string base_exists_name;
};

const std::string ZLightUniformDescriptor::base_position_name = "position";
const std::string ZLightUniformDescriptor::base_color_name = "color";
const std::string ZLightUniformDescriptor::base_exists_name = "exists";

const char *__vertex_shader_source =
#include "vertex.vsh.h"
;

const char *__fragment_shader_source =
#include "fragment.fsh.h"
;

#pragma mark -

static ZUniformRef __create_uniform(GLenum type, std::string name, GLuint index);
static ZLightUniformDescriptor __uniform_descriptor_for_light_type(ZLightType type);

ZRenderContext* ZRenderContext::__current_context = nullptr;

#pragma mark -

ZRenderContext::ZRenderContext() :
    _render_scale(1.0),
    _shaders_initialized(false),
    _depth_testing_enabled(false)
{
    for (unsigned i = 0; i < _ZRENDER_MATRIX_COUNT; ++i) {
        _matrix_stacks[i].push(ZMatrix::identity());
    }
}

ZRenderContext::~ZRenderContext()
{}

ZRenderContext* ZRenderContext::get_current_context()
{
    return __current_context;
}

#pragma mark - Accessors

ZShaderProgramRef ZRenderContext::get_shader_program() const { return _shader_program; }

#pragma mark - API

ZVertexArrayRef ZRenderContext::create_vertex_array()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    
    auto deleter = [this](uint32_t vao) {
        glDeleteVertexArrays(1, &vao);
    };
    
    return ZVertexArrayRef(new ZVertexArray(vao, deleter));
}

ZGraphicsBufferRef ZRenderContext::create_graphics_buffer(ZBufferTarget target)
{
    GLuint buffer_name;
    glGenBuffers(1, &buffer_name);
    
    auto deleter = [this](uint32_t buffer_name) {
        glDeleteBuffers(1, &buffer_name);
    };

    return ZGraphicsBufferRef(new ZGraphicsBuffer(buffer_name, target, deleter));
}

ZElementGraphicsBufferRef ZRenderContext::create_elements_buffer()
{
    GLuint buffer_name;
    glGenBuffers(1, &buffer_name);
    
    auto deleter = [this](uint32_t buffer_name) {
        glDeleteBuffers(1, &buffer_name);
    };
    
    return ZElementGraphicsBufferRef(new ZElementGraphicsBuffer(buffer_name, deleter));
}

ZShaderProgramRef ZRenderContext::create_shader_program()
{
    uint32_t handle = glCreateProgram();
    
    auto deleter = [](uint32_t handle) {
        glDeleteProgram(handle);
    };
    auto attach = [](uint32_t handle, uint32_t shader) {
        glAttachShader(handle, shader);
    };
    auto detach = [](uint32_t handle, uint32_t shader) {
        glDetachShader(handle, shader);
    };
    auto link = [](uint32_t handle, std::map<uint32_t, std::string> attributes) {
        ZShaderProgramLinkResult result;
        
        for (const auto &attrib_pair : attributes) {
            glBindAttribLocation(handle, attrib_pair.first, attrib_pair.second.c_str());
        }
        
        glLinkProgram(handle);
        
        GLint status;
        glGetProgramiv(handle, GL_LINK_STATUS, &status);
        if (status == GL_TRUE) {
            // load uniforms
            std::vector<ZUniformRef> uniforms;
            GLint uniforms_count = 0;
            glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &uniforms_count);
            
            const unsigned name_buf_size = 128;
            char uniform_name_buf[name_buf_size];
            for (unsigned i = 0; i < uniforms_count; ++i) {
                GLenum type;
                GLint location;
                
                glGetActiveUniform(handle, i, name_buf_size, NULL, NULL, &type, uniform_name_buf);
                location = glGetUniformLocation(handle, uniform_name_buf);
                
                std::string name = uniform_name_buf;
                ZUniformRef uniform = __create_uniform(type, name, location);
                uniforms.push_back(uniform);
            }
            
            result.success = true;
            result.uniforms = uniforms;
        } else {
            GLint errlen;
            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &errlen);
            
            std::vector<char> errdata(errlen);
            glGetProgramInfoLog(handle, errlen, 0, errdata.data());
            
            result.success = false;
            result.error = errdata.data();
        }
        
        return result;
    };
    
    ZShaderProgramCallbacks callbacks = {
        .destroy = deleter,
        .attach = attach,
        .detach = detach,
        .link = link
    };
    return ZShaderProgramRef(new ZShaderProgram(handle, callbacks));
}

ZShaderRef ZRenderContext::create_shader(ZShaderType type)
{
    ZShaderRef shader = nullptr;
    GLenum gltype = ZGLUtil::gl_shader_type_from_shader_type(type);
    
    if (gltype != 0) {
        uint32_t handle = glCreateShader(gltype);
        
        auto deleter = [](uint32_t handle) {
            glDeleteShader(handle);
        };
        auto load = [](uint32_t handle, const std::string &src) {
            const char *src_str = src.c_str();
            glShaderSource(handle, 1, &src_str, nullptr);
        };
        auto compile = [](uint32_t handle) {
            ZShaderCompilationResult result;
            glCompileShader(handle);
            
            GLint status = GL_FALSE;
            glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
            if (status == GL_TRUE) {
                result.success = true;
            } else {
                GLint errlen;
                glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &errlen);
                
                std::vector<char> errdata(errlen);
                glGetShaderInfoLog(handle, errlen, 0, errdata.data());
                
                result.success = false;
                result.error = errdata.data();
            }
            
            return result;
        };
        
        ZShaderCallbacks callbacks = {
            .destroy = deleter,
            .load_source = load,
            .compile = compile
        };
        
        shader = ZShaderRef(new ZShader(handle, type, callbacks));
    } else {
        ZException exception(ZENGINE_EXCEPTION_CODE);
        exception.description = "Attempted to create a shader of an unsupported type.";
        throw exception;
    }
    
    return shader;
}

ZTextureRef ZRenderContext::create_texture(ZImageRef image)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    ZSize2D img_size = image->get_size();
    ZDataRef img_data = image->get_pixel_data();
    ZImageFormat img_format = image->get_format();
    GLenum gl_format = ZGLUtil::gl_format_from_pixel_format(img_format.pixel_format);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_size.width, img_size.height, 0, gl_format, GL_UNSIGNED_BYTE, img_data->get_data());
    glBindTexture(GL_TEXTURE_2D, 0);
    
    auto deleter = [](uint32_t tex_name) {
        glDeleteTextures(1, &tex_name);
    };
    
    return ZTextureRef(new ZTexture(texture, image, deleter));
}

ZTextureRef ZRenderContext::create_texture(const std::string &path)
{
    return create_texture(ZImage::create(path));
}

void ZRenderContext::initialize_shaders()
{
    make_current();
    _initialize_gl();
    
    if (!_shader_program) {
        ZShaderProgramRef shader_program = create_shader_program();
        shader_program->load_shader_source(__vertex_shader_source, ZVERTEX_SHADER);
        shader_program->load_shader_source(__fragment_shader_source, ZFRAGMENT_SHADER);
        
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_POSITION, "position");
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_NORMAL, "normal");
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_TEXCOORD0, "texcoord0");
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_COLOR, "color");
        shader_program->link_program();
        
        _use_shader_program(shader_program);
        _shader_program = shader_program;
        
        for (unsigned i = 0; i < _ZRENDER_MATRIX_COUNT; ++i) {
            _update_matrix_uniforms((ZRenderMatrixType)i);
        }
    }
}

void ZRenderContext::push_matrix(ZRenderMatrixType type)
{
    ZMatrix top = _matrix_stacks[type].top();
    _matrix_stacks[type].push(top);
}

void ZRenderContext::push_matrix(ZRenderMatrixType type, const ZMatrix &matrix)
{
    push_matrix(type);
    multiply_matrix(type, matrix);
}

void ZRenderContext::multiply_matrix(ZRenderMatrixType type, const ZMatrix &matrix)
{
    _matrix_stacks[type].top() *= matrix;
    _update_matrix_uniforms(type);
}

void ZRenderContext::load_identity(ZRenderMatrixType type)
{
    _matrix_stacks[type].top() = ZMatrix::identity();
    _update_matrix_uniforms(type);
}

void ZRenderContext::pop_matrix(ZRenderMatrixType type)
{
    if (_matrix_stacks[type].size() > 1) {
        _matrix_stacks[type].pop();
        _update_matrix_uniforms(type);
    } else {
        load_identity(type);
    }
}

ZMatrix ZRenderContext::get_matrix(ZRenderMatrixType type) const
{
    return _matrix_stacks[type].top();
}

ZRect ZRenderContext::get_viewport() const
{
    return _viewport;
}

void ZRenderContext::set_viewport(const ZRect &viewport)
{
    _viewport = viewport;
    _update_viewport();
}

float ZRenderContext::get_render_scale() const
{
    return _render_scale;
}

void ZRenderContext::set_render_scale(float scale)
{
    _render_scale = scale;
    _update_viewport();
}

bool ZRenderContext::depth_testing_is_enabled() const
{
    return _depth_testing_enabled;
}

void ZRenderContext::set_depth_testing_enabled(bool enabled)
{
    if (_depth_testing_enabled != enabled) {
        _depth_testing_enabled = enabled;
        
        make_current();
        
        if (enabled) {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }
}

void ZRenderContext::bind_texture(const ZTextureRef &texture)
{
    GLuint texture_name = texture->get_texture_name();
    glBindTexture(GL_TEXTURE_2D, texture_name);
    _bound_texture = texture;
    
    _set_boolean_uniform("material.textureExists", true);
}

void ZRenderContext::unbind_texture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    _bound_texture = nullptr;
    
    _set_boolean_uniform("material.textureExists", false);
}

void ZRenderContext::bind_vertex_array(const ZVertexArrayRef &varray)
{
    GLuint vao = (GLuint)varray->get_vao_name();
    glBindVertexArray(vao);
    
    const ZVertexBuffersArray &buffers = varray->get_buffers();
    
    for (unsigned i = 0; i < ZVERTEX_ATTRIB_COUNT; ++i) {
        ZVertexAttributeIndex index = (ZVertexAttributeIndex)i;
        ZGraphicsBufferRef buffer = buffers[index];
        if (buffer) {
            GLenum gltarget = ZGLUtil::gl_target_from_buffer_target(buffer->get_target());
            glBindBuffer(gltarget, buffer->get_name());
            _setup_vertex_attrib_ptr(buffer, index);
        }
    }
    
    const ZElementGraphicsBufferRef &element_buffer = varray->get_element_buffer();
    if (element_buffer) {
        GLenum elmtarget = ZGLUtil::gl_target_from_buffer_target(element_buffer->get_target());
        glBindBuffer(elmtarget, element_buffer->get_name());
    }
    
    _bound_vertex_array = varray;
}

void ZRenderContext::unbind_vertex_array()
{
    glBindVertexArray(0);
}

void ZRenderContext::add_light(ZLightRef light)
{
    ZLightType type = light->get_type();
    ZLightUniformDescriptor uniform_descriptor = __uniform_descriptor_for_light_type(type);
    ZShaderProgramRef shader_program = _shader_program;
    
    _lights[type] = light;
    
    // flip lights flag if not set already
    _set_boolean_uniform(uniform_descriptor.exists_name, true);
    
    // setup position uniform
    ZUniformRef pos_uniform = shader_program->get_uniform(uniform_descriptor.position_name);
    pos_uniform->set_data(light->get_position().get_data());
    
    // setup color uniform
    ZUniformRef color_uniform = shader_program->get_uniform(uniform_descriptor.color_name);
    color_uniform->set_data(light->get_color().data);
}

void ZRenderContext::add_lights(const std::vector<ZLightRef> &lights)
{
    for (ZLightRef light : lights) {
        add_light(light);
    }
}

void ZRenderContext::remove_lights(const std::vector<ZLightRef> &lights)
{
    std::vector<ZLightType> light_types_to_clear;
    for (const auto &kv : _lights) {
        ZLightRef stored_light = kv.second;
        if (std::find(lights.begin(), lights.end(), stored_light) != lights.end()) {
            ZLightType light_type = kv.first;
            ZLightUniformDescriptor uniform_descriptor = __uniform_descriptor_for_light_type(light_type);
            _set_boolean_uniform(uniform_descriptor.exists_name, false);
            
            light_types_to_clear.push_back(light_type);
        }
    }
    
    for (ZLightType type_to_clear : light_types_to_clear) {
        _lights.erase(type_to_clear);
    }
}

void ZRenderContext::clear_lights()
{
    for (const auto &kv : _lights) {
        ZLightType light_type = kv.first;
        ZLightUniformDescriptor uniform_descriptor = __uniform_descriptor_for_light_type(light_type);
        _set_boolean_uniform(uniform_descriptor.exists_name, false);
    }
    
    _lights.clear();
}

void ZRenderContext::prepare_render()
{
    if (__current_context != this) {
        make_current();
    }
    
    _clear_buffers();
}

void ZRenderContext::draw_array(ZRenderMode mode, ZVertexArrayRef varray, unsigned first_idx, size_t count)
{
    _update_dirty_uniforms();
    bind_vertex_array(varray);
    
    // flush any pending data
    const ZVertexBuffersArray &buffers = varray->get_buffers();
    for (const ZGraphicsBufferRef &buffer : buffers) {
        if (buffer && buffer->get_pending_buffer().data.get_length() > 0) {
            const ZPendingGraphicsBuffer &pending_buf = buffer->get_pending_buffer();
            const GLenum target = ZGLUtil::gl_target_from_buffer_target(buffer->get_target());
            const GLenum glusage = ZGLUtil::gl_usage_from_buffer_usage(pending_buf.usage);
            glBindBuffer(target, buffer->get_name());
            glBufferData(target, (GLsizeiptr)pending_buf.data.get_length(), (const GLvoid *)pending_buf.data.get_data(), glusage);
            
            buffer->clear_pending_buffer();
        }
    }
    
    GLenum glmode = ZGLUtil::gl_draw_mode_from_render_mode(mode);
    glDrawArrays(glmode, first_idx, (GLsizei)count);
    
    unbind_vertex_array();
}

void ZRenderContext::draw_elements(ZRenderMode mode, ZVertexArrayRef varray)
{
    _update_dirty_uniforms();
    bind_vertex_array(varray);
    
    ZElementGraphicsBufferRef element_buffer = varray->get_element_buffer();
    if (element_buffer.get()) {
        GLenum glmode = ZGLUtil::gl_draw_mode_from_render_mode(mode);
        GLenum indices_type = ZGLUtil::gl_value_type_from_component_type(element_buffer->get_indices_type());
        GLsizei count = (GLsizei)element_buffer->get_elements_count();
        glDrawElements(glmode, count, indices_type, nullptr);
    } else {
        zlog("%s failed. No elements buffer was provided in vertex array %p.", __FUNCTION__, varray.get());
    }
    
    unbind_vertex_array();
}

#pragma mark - Internal

void ZRenderContext::_initialize_gl()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if !OPENGL_ES
    glEnable(GL_MULTISAMPLE);
#endif
}

void ZRenderContext::_clear_buffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ZRenderContext::_update_viewport()
{
    glViewport(_viewport.origin.x,
               _viewport.origin.y,
               _viewport.size.width * _render_scale,
               _viewport.size.height * _render_scale);
}

ZUniformRef ZRenderContext::_get_matrix_uniform(ZRenderMatrixType type)
{
    static std::string uniform_mapping[_ZRENDER_MATRIX_COUNT] = {
        [ZRENDER_MATRIX_MODELVIEW]  = "modelview",
        [ZRENDER_MATRIX_PROJECTION] = "projection"
    };
    ZUniformRef uniform = nullptr;
    
    if (_shader_program) {
        std::string uniform_name = uniform_mapping[type];
        uniform = _shader_program->get_uniform(uniform_name);
    }
    
    return uniform;
}

void ZRenderContext::_update_matrix_uniforms(ZRenderMatrixType type)
{
    ZUniformRef uniform = _get_matrix_uniform(type);
    if (uniform) {
        const ZMatrix &matrix = _matrix_stacks[type].top();
        uniform->set_data(matrix.get_data());
    } else {
        ZLogger::log_error("Could not get uniform for matrix type %d.", type);
    }
}

void ZRenderContext::_set_boolean_uniform(const std::string uniform_name, bool flag)
{
    ZUniformRef uniform = _shader_program->get_uniform(uniform_name);
    int uniform_data = (flag ? 1 : 0);
    uniform->set_data(&uniform_data);
}

void ZRenderContext::_setup_vertex_attrib_ptr(const ZGraphicsBufferRef &buffer, ZVertexAttributeIndex index)
{
    glEnableVertexAttribArray(index);
    
    const std::vector<ZBufferAttribute> &attributes = buffer->get_attributes();
    for (const ZBufferAttribute &attribute : attributes) {
        GLboolean normalized_val = attribute.normalized ? GL_TRUE : GL_FALSE;
        GLenum value_type = ZGLUtil::gl_value_type_from_component_type(attribute.component_type);
        glVertexAttribPointer(index, attribute.components_per_vertex, value_type, normalized_val, (GLsizei)attribute.stride, (const GLvoid *)attribute.offset);
    }
}

void ZRenderContext::_use_shader_program(const ZShaderProgramRef &program)
{
    if (program->is_linked()) {
        uint32_t handle = program->get_program_handle();
        glUseProgram(handle);
    }
}

void ZRenderContext::_update_dirty_uniforms()
{
    const std::vector<ZUniformRef> &dirty_uniforms = _shader_program->get_dirty_uniforms();
    for (const ZUniformRef &uniform : dirty_uniforms) {
        _update_uniform_data(uniform);
    }
}

void ZRenderContext::_update_uniform_data(const ZUniformRef &uniform)
{
    GLenum type = uniform->get_type();
    GLint location = uniform->get_location();
    size_t length = 0;
    const void *data = uniform->get_data(&length);
    
    switch (type) {
        case GL_FLOAT:
            glUniform1fv(location, 1, (const GLfloat *)data);
            break;
        case GL_FLOAT_VEC2:
            glUniform2fv(location, 1, (const GLfloat *)data);
            break;
        case GL_FLOAT_VEC3:
            glUniform3fv(location, 1, (const GLfloat *)data);
            break;
        case GL_FLOAT_VEC4:
            glUniform4fv(location, 1, (const GLfloat *)data);
            break;
        case GL_INT:
            glUniform1iv(location, 1, (const GLint *)data);
            break;
        case GL_INT_VEC2:
            glUniform2iv(location, 1, (const GLint *)data);
            break;
        case GL_INT_VEC3:
            glUniform3iv(location, 1, (const GLint *)data);
            break;
        case GL_INT_VEC4:
            glUniform4iv(location, 1, (const GLint *)data);
            break;
        case GL_UNSIGNED_INT:
            glUniform1uiv(location, 1, (const GLuint *)data);
            break;
        case GL_UNSIGNED_INT_VEC2:
            glUniform2uiv(location, 1, (const GLuint *)data);
            break;
        case GL_UNSIGNED_INT_VEC3:
            glUniform3uiv(location, 1, (const GLuint *)data);
            break;
        case GL_UNSIGNED_INT_VEC4:
            glUniform4uiv(location, 1, (const GLuint *)data);
            break;
        case GL_FLOAT_MAT2:
            glUniformMatrix2fv(location, 1, GL_FALSE, (const GLfloat *)data);
            break;
        case GL_FLOAT_MAT3:
            glUniformMatrix3fv(location, 1, GL_FALSE, (const GLfloat *)data);
            break;
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat *)data);
            break;
#if !OPENGL_ES
        case GL_SAMPLER_1D:
#endif
        case GL_SAMPLER_2D:
        case GL_SAMPLER_3D:
            glUniform1uiv(location, 1, (const GLuint *)data);
            break;
        default: {
            ZException e(ZNOT_IMPLEMENTED_EXCEPTION_CODE);
            e.extra_info = ZUtil::format("Uniform of type %ld has no API implementation.", (long)type);
            throw e;
            break;
        }
    }
    
    uniform->set_dirty(false);
}

ZUniformRef __create_uniform(GLenum type, std::string name, GLuint index)
{
    ZUniformRef uniform = nullptr;
    
    switch (type) {
        case GL_FLOAT:
            uniform = ZUniformRef(new ZUniform<GLfloat, 1>(name, index, GL_FLOAT));
            break;
        case GL_FLOAT_VEC2:
            uniform = ZUniformRef(new ZUniform<GLfloat, 2>(name, index, GL_FLOAT_VEC2));
            break;
        case GL_FLOAT_VEC3:
            uniform = ZUniformRef(new ZUniform<GLfloat, 3>(name, index, GL_FLOAT_VEC3));
            break;
        case GL_FLOAT_VEC4:
            uniform = ZUniformRef(new ZUniform<GLfloat, 4>(name, index, GL_FLOAT_VEC4));
            break;
        case GL_INT:
            uniform = ZUniformRef(new ZUniform<GLint, 1>(name, index, GL_INT));
            break;
        case GL_INT_VEC2:
            uniform = ZUniformRef(new ZUniform<GLint, 2>(name, index, GL_INT_VEC2));
            break;
        case GL_INT_VEC3:
            uniform = ZUniformRef(new ZUniform<GLint, 3>(name, index, GL_INT_VEC3));
            break;
        case GL_INT_VEC4:
            uniform = ZUniformRef(new ZUniform<GLint, 4>(name, index, GL_INT_VEC4));
            break;
        case GL_UNSIGNED_INT:
            uniform = ZUniformRef(new ZUniform<GLuint, 1>(name, index, GL_UNSIGNED_INT));
            break;
        case GL_UNSIGNED_INT_VEC2:
            uniform = ZUniformRef(new ZUniform<GLuint, 2>(name, index, GL_UNSIGNED_INT_VEC2));
            break;
        case GL_UNSIGNED_INT_VEC3:
            uniform = ZUniformRef(new ZUniform<GLuint, 3>(name, index, GL_UNSIGNED_INT_VEC3));
            break;
        case GL_UNSIGNED_INT_VEC4:
            uniform = ZUniformRef(new ZUniform<GLuint, 4>(name, index, GL_UNSIGNED_INT_VEC4));
            break;
        case GL_FLOAT_MAT2:
            uniform = ZUniformRef(new ZUniform<GLfloat, 2*2>(name, index, GL_FLOAT_MAT2));
            break;
        case GL_FLOAT_MAT3:
            uniform = ZUniformRef(new ZUniform<GLfloat, 3*3>(name, index, GL_FLOAT_MAT3));
            break;
        case GL_FLOAT_MAT4:
            uniform = ZUniformRef(new ZUniform<GLfloat, 4*4>(name, index, GL_FLOAT_MAT4));
            break;
#if !OPENGL_ES
        case GL_SAMPLER_1D:
            uniform = ZUniformRef(new ZUniform<GLuint, 1>(name, index, GL_SAMPLER_1D));
            break;
#endif
        case GL_SAMPLER_2D:
            uniform = ZUniformRef(new ZUniform<GLuint, 1>(name, index, GL_SAMPLER_2D));
            break;
        case GL_SAMPLER_3D:
            uniform = ZUniformRef(new ZUniform<GLuint, 1>(name, index, GL_SAMPLER_3D));
            break;
        default:
            break;
    }
    
    return uniform;
}

ZLightUniformDescriptor __uniform_descriptor_for_light_type(ZLightType type)
{
    std::string uniform_struct_name;
    switch (type) {
        case ZLIGHT_TYPE_AMBIENT:
            uniform_struct_name = "ambientLight";
            break;
        case ZLIGHT_TYPE_POINT:
            uniform_struct_name = "diffuseLight";
            break;
        default:
            throw std::runtime_error("Unknown uniform struct for light type");
            break;
    }
    
    ZLightUniformDescriptor descriptor = {
        .position_name = uniform_struct_name + "." + ZLightUniformDescriptor::base_position_name,
        .color_name = uniform_struct_name + "." + ZLightUniformDescriptor::base_color_name,
        .exists_name = uniform_struct_name + "." + ZLightUniformDescriptor::base_exists_name
    };
    return descriptor;
}

ZGE_END_NAMESPACE
