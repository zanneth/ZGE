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
    _current_display(nullptr)
{}

ZDisplayManager::~ZDisplayManager()
{
    if (_current_display != nullptr) {
        delete _current_display;
    }
}

ZDisplay* ZDisplayManager::create_display(const ZDisplayMode &mode)
{
    ZDisplay *display = new ZGLDisplay(mode);
    display->initialize();
    
    if (_current_display != nullptr) {
        delete _current_display;
    }
    
    _current_display = display;
    return display;
}

void ZDisplayManager::run(unsigned dtime)
{
    if (_current_display != nullptr) {
        if (!_current_display->is_initialized()) {
            _current_display->initialize();
        }
        
        _current_display->render(dtime);
    }
}

} // namespace zge
