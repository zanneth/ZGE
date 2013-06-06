/*
 * shader_program.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/30/2012
 */
 
#include <zge/shader_program.h>
#include <iostream>
#include <fstream>

namespace zge {

ZShaderProgram::ZShaderProgram() :
    _linked(false)
{
    _program = glCreateProgram();
}

ZShaderProgram::~ZShaderProgram()
{
    for (auto shader : _shaders) {
        glDeleteShader(shader);
    }
    
    glDeleteProgram(_program);
}

GLuint ZShaderProgram::compile_shader(const char *filename, GLenum type)
{
    using namespace std;
    string shader_src;
    
    // read the shader source from the filename
    ifstream file(filename, ifstream::in);
    string line;
    while (file.good()) {
        getline(file, line);
        shader_src += line + '\n';
    }
    
    // create the shader
    GLuint shader = glCreateShader(type);
    
    // load source and compile
    const char *shader_cstr = shader_src.c_str();
    glShaderSource(shader, 1, &shader_cstr, NULL);
    glCompileShader(shader);
    
    // check if there's an error and log it
    GLint status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint errlen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errlen);
        
        char *errstr = new char[errlen];
        glGetShaderInfoLog(shader, errlen, 0, errstr);
        std::cerr << errstr << std::endl;
        delete[] errstr;
        
        return 0;
    }
    
    return shader;
}

bool ZShaderProgram::attach_shader(GLuint shader)
{
    if (shader == 0) { return false; }
    
    glAttachShader(_program, shader);
    _shaders.push_back(shader);
    return true;
}

bool ZShaderProgram::detach_shader(GLuint shader)
{
    if (shader == 0) { return false; }
    
    glDetachShader(_program, shader);
    _shaders.erase(std::remove(_shaders.begin(), _shaders.end(), shader), _shaders.end());
    return true;
}

bool ZShaderProgram::load_shader(const char *filename, GLenum type)
{
    GLuint shader = compile_shader(filename, type);
    return attach_shader(shader);
}

bool ZShaderProgram::bind_attribute(ZVertexAttribute attrib, std::string name)
{
    bool success = false;
    if (_attrib_map.find(attrib) == _attrib_map.end()) {
        glBindAttribLocation(_program, attrib, name.c_str());
        _attrib_map[attrib] = name;
        success = true;
    }
    
    return success;
}

bool ZShaderProgram::link_program()
{
    GLint status = GL_FALSE;
    
    if (!_linked) {
        glLinkProgram(_program);
        
        // log the error if there is one
        glGetProgramiv(_program, GL_LINK_STATUS, &status);
        if (!status) {
            // print the error
            GLint errlen;
            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &errlen);
            
            char *errstr = new char[errlen];
            glGetProgramInfoLog(_program, errlen, 0, errstr);
            std::cerr << errstr << std::endl;
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
    if (_linked && _program != 0) {
        glUseProgram(_program);
    }
    return result;
}

GLint ZShaderProgram::get_uniform(std::string name)
{
    GLint uniform = -1;
    
    if (_linked) {
        auto uniform_itr = _uniform_map.find(name);
        if (uniform_itr != _uniform_map.end()) {
            uniform = uniform_itr->second;
        } else {
            uniform = glGetUniformLocation(_program, name.c_str());
            if (uniform != -1) {
                _uniform_map[name] = uniform;
            }
        }
    }
    
    return uniform;
}

} // namespace zge
