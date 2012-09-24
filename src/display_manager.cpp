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

display_manager::display_manager() :
    _current_display(nullptr)
{}

display_manager::~display_manager()
{
    if (_current_display != nullptr) {
        delete _current_display;
    }
}

display* display_manager::create_display(const display_mode &mode)
{
    display *display = new gldisplay(mode);
    display->initialize();
    
    if (_current_display != nullptr) {
        delete _current_display;
    }
    
    _current_display = display;
    return display;
}

void display_manager::run(unsigned dtime)
{
    if (_current_display != nullptr) {
        if (!_current_display->is_initialized()) {
            _current_display->initialize();
        }
        
        _current_display->render(dtime);
    }
}

} // namespace zge
