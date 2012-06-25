/*
 * game_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/game_manager.h"

namespace zge {

#pragma mark - Managing Scenes

ZSceneRef ZGameManager::getCurrentScene() const
{
    if (_sceneStack.empty()) {
        return nullptr;
    }
    
    return _sceneStack.top();
}

void ZGameManager::pushScene(ZSceneRef scene)
{
    _sceneStack.push(scene);
}

ZSceneRef ZGameManager::popScene()
{
    ZSceneRef scene = nullptr;
    if (!_sceneStack.empty()) {
        scene = _sceneStack.top();
        _sceneStack.pop();
    }
    
    return scene;
}


#pragma mark - Runnable Overrides

void ZGameManager::run(unsigned dtime)
{
    ZSceneRef scene = getCurrentScene();
    if (scene.get() != nullptr) {
        scene->update(dtime);
    }
}
    
} // namespace zge
