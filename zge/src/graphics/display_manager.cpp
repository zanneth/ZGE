//
//  display_manager.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "display_manager.h"
#include <zge/graphics/display.h>

namespace zge {

void ZDisplayManager::setCurrentDisplay(shared_ptr<zge::ZDisplay> display)
{
    _currentDisplay = display;
    _currentDisplay->initialize();
}

void ZDisplayManager::run(unsigned dtime)
{
    if (!_currentDisplay) {
        _currentDisplay->render(dtime);
    }
}

}
