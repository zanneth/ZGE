/*
 * game_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/game_manager.h"

namespace zge {
#pragma mark - Managing Scenes

ZSceneRef ZGameManager::get_current_scene()
{
    if (_scene_stack.empty()) {
        return nullptr;
    }
    
    return _scene_stack.top();
}

void ZGameManager::push_scene(ZSceneRef scene)
{
    _scene_stack.push(scene);
    scene->on_enter();
}

ZSceneRef ZGameManager::pop_scene()
{
    ZSceneRef scene = nullptr;
    if (!_scene_stack.empty()) {
        scene = _scene_stack.top();
        _scene_stack.pop();
        scene->on_exit();
    }
    
    return scene;
}

#pragma mark - ZSchedulable Overrides

void ZGameManager::run(uint32_t dtime)
{
    ZSceneRef scene = get_current_scene();
    if (scene.get() != nullptr) {
        scene->_update_internal(dtime);
        scene->_draw_internal();
    }
}
    
} // namespace zge
