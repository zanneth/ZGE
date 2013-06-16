/*
 * scene_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/scene_manager.h>

namespace zge {

#pragma mark - Managing Scenes

ZSceneRef ZSceneManager::get_current_scene()
{
    if (_scene_stack.empty()) {
        return nullptr;
    }
    
    return _scene_stack.top();
}

void ZSceneManager::push_scene(ZSceneRef scene)
{
    _scene_stack.push(scene);
    scene->on_enter();
}

ZSceneRef ZSceneManager::pop_scene()
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

void ZSceneManager::run(uint32_t dtime)
{
    ZSceneRef scene = get_current_scene();
    if (scene.get() != nullptr) {
        scene->_update_internal(dtime);
    }
}
    
} // namespace zge
