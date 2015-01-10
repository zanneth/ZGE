/*
 * shader.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include "shader.h"
#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>
#include <zge/exception.h>
#include <zge/logger.h>
#include <zge/glutil.h>
#include <zge/resource_bundle.h>

ZGE_BEGIN_NAMESPACE

ZShader::ZShader(const ZShaderType &type) :
    _type(type),
    _has_source(false),
    _compiled(false)
{
    GLenum gltype = ZGLUtil::gl_shader_type_from_shader_type(type);
    if (gltype != 0) {
        _shader_handle = glCreateShader(gltype);
    } else {
        ZException exception(ZENGINE_EXCEPTION_CODE);
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
    _shader_source_path = path;
    
    std::string shader_src = _load_and_preprocess_source_file(path);
    const char *shader_cstr = shader_src.c_str();
    glShaderSource(_shader_handle, 1, &shader_cstr, nullptr);
    
    _has_source = true;
    return true;
}

bool ZShader::load_source(const std::string source)
{
    std::ostringstream source_buffer;
    std::stringstream source_in_stream(source);
    std::string line;
    
    while (source_in_stream.good()) {
        std::getline(source_in_stream, line);
        _process_shader_source_line(line, source_buffer);
    }
    
    std::string preprocessed_source = source_buffer.str();
    const char *shader_cstr = preprocessed_source.c_str();
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
        ZLogger::log_error("%s", errstr);
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

GLuint ZShader::_get_shader_handle() const
{
    return _shader_handle;
}

#pragma mark - Internal

std::string ZShader::_load_and_preprocess_source_file(const std::string &path)
{
    std::ostringstream source_buffer;
    
    // read the shader source from the filename
    std::ifstream file(path, std::ifstream::in);
    if (file) {
        std::string line;
        while (file.good()) {
            std::getline(file, line);
            _process_shader_source_line(line, source_buffer);
        }
    } else {
        ZException e(ZFILE_EXCEPTION_CODE);
        e.extra_info = ZUtil::format("Shader source file %s does not exit", path.c_str());
        throw e;
    }
    
    return source_buffer.str();
}

void ZShader::_process_shader_source_line(const std::string &line, std::ostringstream &source_buffer)
{
    static const std::regex directive_re("#pragma (\\w+) (.*)");
    std::smatch directive_match;
    
    bool is_match = std::regex_search(line, directive_match, directive_re);
    if (is_match && directive_match.size() >= 2) {
        _handle_preprocessor_directive(directive_match[1], directive_match[2], source_buffer);
    } else {
        source_buffer << line << std::endl;
    }
}

void ZShader::_handle_preprocessor_directive(const std::string &directive,
                                             const std::string &input,
                                             std::ostringstream &source_buffer)
{
    if (directive == "zge_include") {
        _include_directive_handler(input, source_buffer);
    }
}

void ZShader::_include_directive_handler(const std::string &input, std::ostringstream &source_buffer)
{
    static const std::regex include_syntax_re("\"(.*)\"");
    std::smatch include_match;
    
    bool is_match = std::regex_search(input, include_match, include_syntax_re);
    if (is_match && include_match.size() >= 1) {
        ZResourceBundle *res_bundle = ZResourceBundle::get_main_bundle();
        std::string source_filename = include_match[1];
        std::string source_dirname = res_bundle->get_dirname(_shader_source_path);
        std::string source_path = res_bundle->append_path_component(source_dirname, source_filename);
        
        try {
            std::string shader_source = _load_and_preprocess_source_file(source_path);
            source_buffer << shader_source << std::endl;
        } catch (const ZException &e) {
            ZLogger::log_error("Error loading included shader source at path %s", source_path.c_str());
        }
    }
}

ZGE_END_NAMESPACE
