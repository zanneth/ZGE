/*
 * display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/display.h"
#include "zge/exception.h"

namespace zge {

ZDisplay::ZDisplay(const ZDisplayMode &mode) :
    _displayMode(mode) {}


#pragma mark - Convenience Methods

void ZDisplay::resize(int width, int height)
{
    ZDisplayMode mode = _displayMode;
    mode.width = width;
    mode.height = height;
    
    setDisplayMode(mode);
}


#pragma mark - Accessors

void ZDisplay::setDisplayMode(const ZDisplayMode &mode)
{
    _displayMode = mode;
}

} // namespace zge
