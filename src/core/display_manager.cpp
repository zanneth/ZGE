/*
 * display_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/display_manager.h>
#include <zge/display.h>
#include <zge/engine.h>
#include <zge/exception.h>
#include <zge/render_manager.h>

BEGIN_ZGE_NAMESPACE

ZDisplayManager::ZDisplayManager() :
    _current_display(nullptr)
{}

ZDisplayManager::~ZDisplayManager()
{}

ZDisplayRef ZDisplayManager::create_display(const ZDisplayMode &mode)
{
    ZDisplayRef display = ZDisplayRef(new ZDisplay(mode));
    display->initialize();
    
    _current_display = display;
    
    ZRenderManagerRef render_manager = ZEngine::instance()->get_render_manager();
    render_manager->_setup_display(_current_display);
    
    return _current_display;
}

void ZDisplayManager::run(uint32_t dtime)
{
    if (_current_display != nullptr) {
        if (!_current_display->is_initialized()) {
            _current_display->initialize();
        }
        
        _current_display->update(dtime);
    }
}

END_ZGE_NAMESPACE
