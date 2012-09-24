/*
 * viewport.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 07/01/2012
 */
 
#include "zge/viewport.h"

namespace zge {

viewport::viewport() :
    x(0),
    y(0),
    width(0),
    height(0)
{}

viewport::viewport(GLint x_, GLint y_, GLsizei width_, GLsizei height_) :
    x(x_),
    y(y_),
    width(width_),
    height(height_)
{}

void viewport::open()
{
    glViewport(x, y, width, height);
}

void viewport::close()
{}

} // namespace zge
