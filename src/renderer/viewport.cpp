/*
 * viewport.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 07/01/2012
 */
 
#include <zge/viewport.h>

namespace zge {

ZViewport::ZViewport() :
    x(0),
    y(0),
    width(0),
    height(0)
{}

ZViewport::ZViewport(GLint x_, GLint y_, GLsizei width_, GLsizei height_) :
    x(x_),
    y(y_),
    width(width_),
    height(height_)
{}

void ZViewport::open()
{
    glViewport(x, y, width, height);
}

void ZViewport::close()
{}

} // namespace zge
