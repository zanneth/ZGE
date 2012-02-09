//
//  display.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/display.h"
#include <iostream>

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

void ZDisplay::setCoordinateSystem(const ZCoordinateSystemf &coordSystem)
{
    _coordinateSystem = coordSystem;
}


} // namespace zge