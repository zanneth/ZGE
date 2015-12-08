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

ZRenderManager::~ZRenderManager()
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

#pragma mark - ZSchedulable

void ZRenderManager::run(uint32_t dtime)
{
    _perf_monitor.log_event(ZPERF_EVENT_FRAME_BEGAN);
    
    if (_context && _renderable) {
        _context->prepare_render();
        _renderable->render(_context);
    }
    
    if (_display) {
        _display->update(dtime);
    }
    
    _perf_monitor.log_event(ZPERF_EVENT_FRAME_ENDED);
}

void ZRenderManager::_initialize_render_context()
{
    if (_display && !_initialized) {
        _context = ZDisplayRenderContext::create(_display);
        _context->make_current();
        _initialized = true;
    }
}

ZGE_END_NAMESPACE
