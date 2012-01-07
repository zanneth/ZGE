//
//  display.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "display.h"


namespace zge {

ZDisplay::ZDisplay() :
    _isInitialized(false),
    _coordinateSystem(ZCoordinateSystem(1024, 768, 512))
{}

void ZDisplay::resize(int width, int height)
{
    ZDisplayMode mode = _displayMode;
    mode.width = width;
    mode.height = height;
    
    setDisplayMode(mode);
}


#pragma mark - Accessors

ZError ZDisplay::setDisplayMode(const ZDisplayMode &mode)
{
    _displayMode = mode;
    return ZError::ZErrorNone();
}

ZError ZDisplay::setCoordinateSystem(const ZCoordinateSystem &coordSystem)
{
    _coordinateSystem = coordSystem;
    return ZError::ZErrorNone();
}


}
