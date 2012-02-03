//
//  display_manager.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/display_manager.h"

namespace zge {

void ZDisplayManager::setCurrentDisplay(ZDisplayRef display)
{
    _currentDisplay = display;
}

void ZDisplayManager::run(unsigned dtime)
{
    if (_currentDisplay.get() != NULL) {
        if (!_currentDisplay->isInitialized()) {
            _currentDisplay->initialize();
        }
        
        _currentDisplay->render(dtime);
    }
}

} // namespace zge