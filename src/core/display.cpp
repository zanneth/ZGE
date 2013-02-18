/*
 * display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/display.h>
#include <zge/exception.h>

namespace zge {

ZDisplay::ZDisplay(const ZDisplayMode &mode) :
    _display_mode(mode) {}

#pragma mark - Convenience Methods

void ZDisplay::resize(int width, int height)
{
    ZDisplayMode mode = _display_mode;
    mode.width = width;
    mode.height = height;
    
    set_display_mode(mode);
}

#pragma mark - Accessors

void ZDisplay::set_display_mode(const ZDisplayMode &mode)
{
    _display_mode = mode;
}

} // namespace zge
