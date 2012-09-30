/*
 * gl_buffer.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */
 
#pragma once

#include "zge/gl_includes.h"
#include "zge/noncopyable.h"
#include <memory>

#define ZUNALLOCATED_BUFFER 0

namespace zge {

typedef std::shared_ptr<struct ZGLBuffer> ZGLBufferRef;

struct ZGLBuffer : ZNoncopyable {
    GLuint name;

public:
    ZGLBuffer();
    ZGLBuffer(ZGLBuffer&&);
    ~ZGLBuffer();
    
    ZGLBuffer& operator=(ZGLBuffer&&);
};

} // namespace zge
