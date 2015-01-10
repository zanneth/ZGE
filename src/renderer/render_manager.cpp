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
#include <zge/scene.h>

ZGE_BEGIN_NAMESPACE

ZRenderManager::ZRenderManager() :
    _context(nullptr),
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

ZSceneRef ZRenderManager::get_scene() const { return _scene; }

void ZRenderManager::set_scene(ZSceneRef scene)
{
    if (_scene) {
        _scene->on_exit();
    }
    
    _scene = scene;
    
    if (_scene) {
        _scene->on_enter();
    }
}

#pragma mark - Overrides

void ZRenderManager::run(uint32_t dtime)
{
    if (_context) {
        _context->make_current();
        _context->clear_buffers();
        
        if (_scene) {
            _scene->_update_internal();
            _scene->_draw(_context);
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
