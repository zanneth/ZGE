/*
 * shader_program.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/30/2012
 */
 
#include <zge/shader_program.h>
#include <zge/exception.h>
#include <zge/opengl.h>
#include <zge/logger.h>
#include <zge/util.h>

ZGE_BEGIN_NAMESPACE

static ZUniformRef _create_uniform(GLenum type, std::string name, GLuint index);

ZShaderProgram::ZShaderProgram() :
    _linked(false),
    _uniforms_loaded(false)
{
    _program_handle = glCreateProgram();
}

ZShaderProgram::~ZShaderProgram()
{
    for (auto &uniform_pair : _uniform_map) {
        ZUniformRef uniform = uniform_pair.second;
        uniform->remove_all_observers();
    }
    
    glDeleteProgram(_program_handle);
}

bool ZShaderProgram::attach_shader(ZShaderRef shader)
{
    bool success = false;
    
    if (shader != nullptr && shader->is_compiled()) {
        glAttachShader(_program_handle, shader->_get_shader_handle());
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
        glDetachShader(_program_handle, shader->_get_shader_handle());
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
            ZLogger::log_error("%s", errstr);
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

ZUniformRef ZShaderProgram::get_uniform(std::string name)
{
    ZUniformRef uniform = nullptr;
    
    if (_linked) {
        if (!_uniforms_loaded) {
            _load_uniforms();
        }
        
        auto uniform_itr = _uniform_map.find(name);
        if (uniform_itr != _uniform_map.end()) {
            uniform = uniform_itr->second;
        }
    }
    
    return uniform;
}

void ZShaderProgram::_load_uniforms()
{
    if (!_uniforms_loaded) {
        if (!_linked) {
            link_program();
        }
        
        GLint uniforms_count = 0;
        glGetProgramiv(_program_handle, GL_ACTIVE_UNIFORMS, &uniforms_count);
        
        const unsigned name_buf_size = 128;
        char uniform_name_buf[name_buf_size];
        for (unsigned i = 0; i < uniforms_count; ++i) {
            GLenum type;
            GLint location;
            
            glGetActiveUniform(_program_handle, i, name_buf_size, NULL, NULL, &type, uniform_name_buf);
            location = glGetUniformLocation(_program_handle, uniform_name_buf);
            
            std::string name = uniform_name_buf;
            ZUniformRef uniform = _create_uniform(type, name, location);
            std::weak_ptr<ZShaderProgram> weak_this = shared_from_this();
            uniform->add_observer([weak_this](ZUniformRef changed_uniform) {
                ZShaderProgramRef strong_this = weak_this.lock();
                if (strong_this.get()) {
                    strong_this->_uniform_modified(changed_uniform);
                }
            });
            
            _uniform_map[name] = uniform;
        }
        
        _uniforms_loaded = true;
    }
}

void ZShaderProgram::_uniform_modified(ZUniformRef uniform)
{
    GLenum type = uniform->get_type();
    GLint location = uniform->_get_location();
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
}

ZUniformRef _create_uniform(GLenum type, std::string name, GLuint index)
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

ZGE_END_NAMESPACE
