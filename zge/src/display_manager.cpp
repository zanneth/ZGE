/*
 * display_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/display_manager.h"
#include "zge/display.h"
#include "zge/exception.h"
#include "zge/gl_display.h"

#include <iostream>

namespace zge {

ZDisplayManager::ZDisplayManager() :
    _currentDisplay(nullptr)
{}

ZDisplayManager::~ZDisplayManager()
{
    if (_currentDisplay != nullptr) {
        delete _currentDisplay;
    }
}

ZDisplay* ZDisplayManager::createDisplay(const ZDisplayMode &mode, ZRenderingAPIType api)
{
    ZDisplay *display = nullptr;
    
    switch (api) {
        case kOpenGL:
            display = new ZGLDisplay(mode);
            break;
        case kSoftware:
        case kDirectX:
        default:
            throw ZNotImplementedException();
            break;
    }
    
    display->initialize();
    
    if (_currentDisplay != nullptr) {
        delete _currentDisplay;
    }
    
    _currentDisplay = display;
    return display;
}

void ZDisplayManager::run(unsigned dtime)
{
    if (_currentDisplay != nullptr) {
        if (!_currentDisplay->isInitialized()) {
            _currentDisplay->initialize();
        }
        
        _currentDisplay->render(dtime);
    }
}

} // namespace zge
