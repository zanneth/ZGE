/*
 * render_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <functional>
#include <zge/render_manager.h>
#include <zge/display_manager.h>
#include <zge/engine.h>
#include <zge/node.h>
#include <zge/scene.h>

BEGIN_ZGE_NAMESPACE

ZRenderManager::ZRenderManager() :
    _context(nullptr),
    _initialized(false)
{}

ZRenderManager::~ZRenderManager()
{}

#pragma mark - Accessors

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
    if (_context != nullptr) {
        if (!_initialized) {
            _initialize();
        }
        
        _context->make_current();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (_scene.get() != nullptr) {
            _scene->_update();
            _scene->_draw(_context);
        }
    }
}

#pragma mark - Internal

void ZRenderManager::_setup_display(ZDisplayRef display)
{
    _context = ZRenderContextRef(new ZRenderContext(display));
}

void ZRenderManager::_initialize()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    _initialized = true;
}

END_ZGE_NAMESPACE
