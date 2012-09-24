/*
 * display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/display.h"
#include "zge/exception.h"

namespace zge {

display::display(const display_mode &mode) :
    _display_mode(mode) {}


#pragma mark - Convenience Methods

void display::resize(int width, int height)
{
    display_mode mode = _display_mode;
    mode.width = width;
    mode.height = height;
    
    set_display_mode(mode);
}


#pragma mark - Accessors

void display::set_display_mode(const display_mode &mode)
{
    _display_mode = mode;
}

} // namespace zge
