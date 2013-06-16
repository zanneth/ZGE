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
#include <zge/scene_manager.h>
#include <zge/node.h>
#include <zge/scene.h>

namespace zge {

ZRenderManager::ZRenderManager() :
    _context(nullptr),
    _initialized(false),
    _shaders_loaded(false)
{
    auto func = std::bind(&ZRenderManager::_display_notification, this, std::placeholders::_1);
    _display_observer = ZNotificationCenter::instance()->add_observer(ZDisplayManagerDidCreateDisplayNotification, func);
}

ZRenderManager::~ZRenderManager()
{
    ZNotificationCenter::instance()->remove_observer(_display_observer);
}

#pragma mark - Accessors

ZRenderContextRef ZRenderManager::get_context() const { return _context; }

#pragma mark - Overrides

void ZRenderManager::run(uint32_t dtime)
{
    if (!_initialized) {
        _initialize();
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ZSceneManagerRef scene_manager = ZEngine::instance()->get_scene_manager();
    ZSceneRef cur_scene = scene_manager->get_current_scene();
    if (cur_scene.get() != nullptr) {
        cur_scene->_draw_internal(_context);
    }
}

#pragma mark - Internal

void ZRenderManager::_initialize()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    _initialized = true;
}

void ZRenderManager::_display_notification(const ZNotification *notification)
{
    if (notification->sender != nullptr) {
        ZDisplayManager *display_manager = static_cast<ZDisplayManager *>(notification->sender);
        ZDisplayRef current_display = display_manager->get_current_display();
        if (current_display != nullptr) {
            _context = ZRenderContextRef(new ZRenderContext(current_display));
        }
    }
}

} // namespace zge
