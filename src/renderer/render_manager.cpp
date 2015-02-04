/*
 * render_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <functional>
#include <zge/render_manager.h>
#include <zge/display.h>
#include <zge/display_render_context.h>
#include <zge/engine.h>
#include <zge/node.h>

ZGE_BEGIN_NAMESPACE

ZRenderManager::ZRenderManager() :
    _display(nullptr),
    _context(nullptr),
    _renderable(nullptr),
    _initialized(false)
{}

#pragma mark - Creating a Display

ZDisplayRef ZRenderManager::create_display(const zge::ZDisplayMode &mode)
{
    _display = ZDisplayRef(new ZDisplay(mode));
    _display->initialize();
    
    _initialize_render_context();
    
    return _display;
}

#pragma mark - Accessors

ZDisplayRef ZRenderManager::get_current_display() const { return _display; }

ZRenderContextRef ZRenderManager::get_context() const { return _context; }

ZRenderableRef ZRenderManager::get_renderable() const { return _renderable; }

void ZRenderManager::set_renderable(ZRenderableRef renderable) { _renderable = renderable; }

#pragma mark - Overrides

void ZRenderManager::run(uint32_t dtime)
{
    if (_context) {
        _context->make_current();
        _context->clear_buffers();
        
        if (_renderable) {
            _renderable->render(_context);
        }
    }
    
    if (_display) {
        _display->update(dtime);
    }
}

#pragma mark - Internal

void ZRenderManager::_initialize_render_context()
{
    if (!_display) {
        return;
    }
    
    if (!_initialized) {
        _context = ZDisplayRenderContext::create(_display);
        _initialized = true;
    }
}

ZGE_END_NAMESPACE
