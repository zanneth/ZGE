/*
 * render_context.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <zge/render_context.h>
#include <zge/glutil.h>
#include <zge/light.h>
#include <zge/logger.h>
#include <zge/resource_bundle.h>
#include <zge/util.h>
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

#pragma mark -

static ZLightUniformDescriptor __uniform_descriptor_for_light_type(ZLightType type);

#pragma mark -

ZRenderContext::ZRenderContext() :
    _render_scale(1.0),
    _shaders_initialized(false)
{
    for (unsigned i = 0; i < _ZRENDER_MATRIX_COUNT; ++i) {
        _matrix_stacks[i].push(ZMatrix::identity());
    }
}

ZRenderContext::~ZRenderContext()
{}

#pragma mark - Accessors

ZShaderProgramRef ZRenderContext::get_shader_program() const { return _shader_program; }

#pragma mark - API

void ZRenderContext::initialize_shaders()
{
    make_current();
    _initialize_gl();
    
    if (!_shader_program) {
        ZShaderProgramRef shader_program = ZShaderProgram::create();
        
        ZResourceBundle *res_bundle = ZResourceBundle::get_library_bundle();
        std::string vert_shader_path = res_bundle->get_path_for_resource("vertex.vsh");
        std::string frag_shader_path = res_bundle->get_path_for_resource("fragment.fsh");
        shader_program->load_shader(vert_shader_path, ZVERTEX_SHADER);
        shader_program->load_shader(frag_shader_path, ZFRAGMENT_SHADER);
        
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_POSITION, "position");
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_NORMAL, "normal");
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_TEXCOORD0, "texcoord0");
        shader_program->bind_attribute_index(ZVERTEX_ATTRIB_COLOR, "color");
        shader_program->link_program();
        
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

void ZRenderContext::bind_texture(ZTextureRef texture)
{
    GLuint texture_name = texture->_get_texture_name();
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

void ZRenderContext::enable_depth_testing()
{
    make_current();
    glEnable(GL_DEPTH_TEST);
}

void ZRenderContext::disable_depth_testing()
{
    make_current();
    glDisable(GL_DEPTH_TEST);
}

void ZRenderContext::clear_buffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ZRenderContext::draw_array(ZRenderMode mode, ZVertexArrayRef varray, unsigned first_idx, size_t count)
{
    varray->_bind();
    _bound_vertex_array = varray;
    
    GLenum glmode = ZGLUtil::gl_draw_mode_from_render_mode(mode);
    glDrawArrays(glmode, first_idx, (GLsizei)count);
}

void ZRenderContext::draw_elements(ZRenderMode mode, ZVertexArrayRef varray)
{
    varray->_bind();
    _bound_vertex_array = varray;
    
    ZElementGraphicsBufferRef element_buffer = varray->get_element_buffer();
    if (element_buffer.get()) {
        GLenum glmode = ZGLUtil::gl_draw_mode_from_render_mode(mode);
        GLenum indices_type = ZGLUtil::gl_value_type_from_component_type(element_buffer->get_indices_type());
        GLsizei count = (GLsizei)element_buffer->get_elements_count();
        glDrawElements(glmode, count, indices_type, nullptr);
    } else {
        zlog("%s failed. No elements buffer was provided in vertex array %p.", __FUNCTION__, varray.get());
    }
}

#pragma mark - Internal

void ZRenderContext::_initialize_gl()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    _shader_program->use_program();
    
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
