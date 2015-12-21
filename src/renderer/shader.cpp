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
#include <zge/resource_bundle.h>

ZGE_BEGIN_NAMESPACE

using ZDirectiveHandler = std::function<void(const std::string&, std::ostringstream&)>;

ZShader::ZShader(uint32_t handle, const ZShaderType &type, const ZShaderCallbacks &callbacks) :
    _shader_handle(handle),
    _callbacks(callbacks),
    _type(type),
    _has_source(false),
    _compiled(false)
{}

ZShader::~ZShader()
{
    _callbacks.destroy(_shader_handle);
}

#pragma mark - API

bool ZShader::load_source_file(const std::string path)
{
    _shader_source_path = path;
    
    std::string shader_src = _load_and_preprocess_source_file(path);
    _callbacks.load_source(_shader_handle, shader_src);
    
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
    _callbacks.load_source(_shader_handle, preprocessed_source);
    
    _has_source = true;
    return true;
}

bool ZShader::compile()
{
    if (!_has_source) {
        ZLogger::log_error("Could not compile shader. No source provided.");
        return false;
    }
    
    ZShaderCompilationResult result = _callbacks.compile(_shader_handle);
    if (!result.success) {
        zlog("SHADER COMPILATION ERROR: %s", result.error.c_str());
    }
    
    _compiled = result.success;
    return result.success;
}

#pragma mark - Accessors

ZShaderType ZShader::get_type() const { return _type; }

uint32_t ZShader::get_handle() const { return _shader_handle; }

bool ZShader::has_source() const { return _has_source; }

bool ZShader::is_compiled() const { return _compiled; }

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
    #define BIND_FUNC(FUNC_NAME) std::bind(&ZShader::FUNC_NAME, this, std::placeholders::_1, std::placeholders::_2)
    
    std::map<std::string, ZDirectiveHandler> directive_map = {
        { "zge_include", BIND_FUNC(_include_directive_handler) },
        { "zge_version", BIND_FUNC(_version_directive_handler) }
    };
    
    try {
        directive_map[directive](input, source_buffer);
    } catch (const std::out_of_range &e) {
        ZLogger::log_error("Warning: no matching pragma directive named %s", directive.c_str());
    }
}

void ZShader::_include_directive_handler(const std::string &input, std::ostringstream &source_buffer)
{
    static const std::regex include_syntax_re("\"(.*)\"");
    std::smatch include_match;
    
    bool is_match = std::regex_search(input, include_match, include_syntax_re);
    if (is_match && include_match.size() >= 1) {
        const ZResourceBundle *res_bundle = ZResourceBundle::get_main_bundle();
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

void ZShader::_version_directive_handler(const std::string &input, std::ostringstream &source_buffer)
{
#if !OPENGL_ES
    std::string glsl_version = "#version " + input;
    source_buffer << glsl_version << std::endl;
#endif
}

ZGE_END_NAMESPACE
