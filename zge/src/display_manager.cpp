/*
 * display_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
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
