/*
 * viewport.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 07/01/2012
 */
 
#pragma once

#include "zge/vector.h"

namespace zge {

class ZViewport {
public:
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    
public:
    ZViewport();
    ZViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    
    void open();
    void close();
};

} // namespace zge
