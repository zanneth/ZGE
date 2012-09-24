/*
 * viewport.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 07/01/2012
 */
 
#pragma once

#include "zge/gl_includes.h"
#include "zge/vector.h"

namespace zge {

class viewport {
public:
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    
public:
    viewport();
    viewport(GLint x, GLint y, GLsizei width, GLsizei height);
    
    void open();
    void close();
};

} // namespace zge
