/*
 * game_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/game_manager.h"

namespace zge {

ZGameManager::~ZGameManager()
{
    while (!_sceneStack.empty()) {
        ZScene *scene = _sceneStack.top();
        delete scene;
        
        _sceneStack.pop();
    }
}


#pragma mark - Creating Scenes

ZScene* ZGameManager::createAndPushScene()
{
    ZScene *scene = new ZScene();
    pushScene(scene);
    
    return scene;
}


#pragma mark - Managing Scenes

ZScene* ZGameManager::getCurrentScene() const
{
    if (_sceneStack.empty()) {
        return nullptr;
    }
    
    return _sceneStack.top();
}

void ZGameManager::pushScene(ZScene *scene)
{
    _sceneStack.push(scene);
}

ZScene* ZGameManager::popScene()
{
    ZScene *scene = nullptr;
    if (!_sceneStack.empty()) {
        scene = _sceneStack.top();
        _sceneStack.pop();
    }
    
    return scene;
}


#pragma mark - Runnable Overrides

void ZGameManager::run(unsigned dtime)
{
    ZScene *scene = getCurrentScene();
    if (scene != nullptr) {
        scene->update(dtime);
    }
}
    
} // namespace zge
