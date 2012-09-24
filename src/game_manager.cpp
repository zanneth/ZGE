/*
 * game_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/game_manager.h"

namespace zge {

#pragma mark - Managing Scenes

scene_ref game_manager::get_current_scene()
{
    if (_scene_stack.empty()) {
        return nullptr;
    }
    
    return _scene_stack.top();
}

void game_manager::push_scene(scene_ref scene)
{
    _scene_stack.push(scene);
    scene->on_enter();
}

scene_ref game_manager::pop_scene()
{
    scene_ref scene = nullptr;
    if (!_scene_stack.empty()) {
        scene = _scene_stack.top();
        _scene_stack.pop();
        scene->on_exit();
    }
    
    return scene;
}


#pragma mark - schedulable Overrides

void game_manager::run(unsigned dtime)
{
    scene_ref scene = get_current_scene();
    if (scene.get() != nullptr) {
        scene->_update_internal(dtime);
        scene->_draw_internal();
    }
}
    
} // namespace zge
