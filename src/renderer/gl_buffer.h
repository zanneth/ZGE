/*
 * gl_buffer.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */
 
#pragma once

#include <zge/noncopyable.h>
#include <zge/gl_includes.h>

#include <memory>

#define ZUNALLOCATED_BUFFER 0
#define ZUNBOUND_TARGET     0

namespace zge {

typedef std::shared_ptr<class ZGLBuffer> ZGLBufferRef;

class ZGLBuffer : ZNoncopyable {
    GLuint _buffer;
    GLenum _target;

public:
    ZGLBuffer();
    ZGLBuffer(ZGLBuffer&&);
    ~ZGLBuffer();
    
    ZGLBuffer& operator=(ZGLBuffer&&);
    
    /** Accessors **/
    GLuint get_buffer() { return _buffer; }
    GLenum get_target() { return _target; }
    void set_target(GLenum target) { _target = target; }
    
    /** Loading Data **/
    void load_data(GLsizeiptr size, const GLvoid *data, GLenum usage);
    
    /** Actions **/
    void bind();
};

} // namespace zge
