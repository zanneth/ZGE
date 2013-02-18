/*
 * gl_buffer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */

#include <zge/gl_buffer.h>
#include <zge/exception.h>
#include <zge/logger.h>

namespace zge {

ZGLBuffer::ZGLBuffer() :
    _buffer(ZUNALLOCATED_BUFFER),
    _target(ZUNBOUND_TARGET)
{
    glGenBuffers(1, &_buffer);
}

ZGLBuffer::ZGLBuffer(ZGLBuffer &&mv)
{
    _buffer = mv._buffer;
    _target = mv._target;
    mv._buffer = ZUNALLOCATED_BUFFER;
    mv._target = ZUNBOUND_TARGET;
}

ZGLBuffer::~ZGLBuffer()
{
    if (_buffer != ZUNALLOCATED_BUFFER) {
        ZLogger::log("Buffer %x deleted.", this);
        glDeleteBuffers(1, &_buffer);
    }
}

ZGLBuffer& ZGLBuffer::operator=(ZGLBuffer &&mv)
{
    _buffer = mv._buffer;
    _target = mv._target;
    mv._buffer = ZUNALLOCATED_BUFFER;
    mv._target = ZUNBOUND_TARGET;
    return *this;
}

#pragma mark - Loading Data

void ZGLBuffer::load_data(GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    if (_target == ZUNBOUND_TARGET) {
        ZException e(ENGINE_EXCEPTION_CODE);
        e.extra_info = "Attempted to load data into a buffer with no target buffer object.";
        throw e;
    }
    
    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
    bind();
    glBufferData(_target, size, data, usage);
    glPopClientAttrib();
}

#pragma mark - Actions

void ZGLBuffer::bind()
{
    glBindBuffer(_target, _buffer);
}

} // namespace zge
