/*
 * render_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <zge/render_manager.h>
#include <zge/engine.h>
#include <zge/game_manager.h>
#include <zge/node.h>
#include <zge/scene.h>

namespace zge {

ZRenderManager::ZRenderManager() :
    _initialized(false)
{}

ZRenderManager::~ZRenderManager()
{}

void ZRenderManager::run(uint32_t dtime)
{
    if (!_initialized) {
        _initialize();
    }
    
    ZGameManagerRef game_manager = ZEngine::instance()->get_game_manager();
    ZSceneRef cur_scene = game_manager->get_current_scene();
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

} // namespace zge
