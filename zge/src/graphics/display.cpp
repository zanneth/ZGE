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
    _isInitialized(false)
{
    ZDisplayMode mode;
    mode.windowed = true;
    mode.width = 800;
    mode.height = 600;
    mode.refreshRate = 1.0 / 60.0;
    mode.windowTitle = "Application";
    setDisplayMode(mode);
    
    ZCoordinateSystem defaultCoordSystem(1024, 768, 512);
    setCoordinateSystem(defaultCoordSystem);
}

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
    return ZErrorNone;
}

ZError ZDisplay::setCoordinateSystem(const ZCoordinateSystem &coordSystem)
{
    _coordinateSystem = coordSystem;
    return ZErrorNone;
}


}
