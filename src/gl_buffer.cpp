/*
 * gl_buffer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */

#include "zge/gl_buffer.h"
#include "zge/exception.h"
#include "zge/logger.h"

namespace zge {

void _copy_buffer(GLuint destination, GLuint source);

ZGLBuffer::ZGLBuffer() :
    name(ZUNALLOCATED_BUFFER)
{
    glGenBuffers(1, &name);
}

ZGLBuffer::ZGLBuffer(ZGLBuffer &&mv)
{
    name = mv.name;
    mv.name = ZUNALLOCATED_BUFFER;
}

ZGLBuffer::~ZGLBuffer()
{
    ZLogger::log("Buffer %x deleted.", this);
    glDeleteBuffers(1, &name);
}

ZGLBuffer& ZGLBuffer::operator=(ZGLBuffer &&cp)
{
    name = cp.name;
    cp.name = ZUNALLOCATED_BUFFER;
    return *this;
}

} // namespace zge
