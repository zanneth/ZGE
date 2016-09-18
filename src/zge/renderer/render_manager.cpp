/*
 * render_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <functional>
#include <zge/renderer/render_manager.h>
#include <zge/core/display.h>
#include <zge/renderer/display_render_context.h>
#include <zge/core/engine.h>
#include <zge/graph/node.h>

ZGE_BEGIN_NAMESPACE

ZRenderManager::ZRenderManager() :
    _display(nullptr),
    _context(nullptr),
    _renderable(nullptr),
    _current_fps(0.0),
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

float ZRenderManager::get_current_frames_per_second() const { return _current_fps; }

#pragma mark - ZSchedulable

void ZRenderManager::run(uint32_t dtime)
{
    if (_context && _renderable) {
        _context->prepare_render();
        _renderable->render(_context);
    }
    
    if (_display) {
        _display->update(dtime);
    }
    
    ZTime now = ZUtil::get_current_time();
    ZTimeInterval dur = now - _last_frame_drawn;
    _current_fps = (1.0 / dur.count());
    _last_frame_drawn = ZUtil::get_current_time();
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
