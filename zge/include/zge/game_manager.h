/*
 * game_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/runnable_interface.h"
#include "zge/noncopyable.h"
#include "zge/node.h"
#include "zge/scene.h"

#include <stack>
#include <memory>

namespace zge {

typedef std::shared_ptr<class ZGameManager> ZGameManagerRef;

class ZGameManager : public ZRunnableInterface, ZNonCopyable {
    std::stack<ZScene*> _sceneStack;
    
public:
    ~ZGameManager();
    
    /** Creating Scenes **/
    ZScene* createAndPushScene();
    
    
    /** Scene Management **/
    ZScene* getCurrentScene() const;
    void pushScene(ZScene *scene);
    ZScene* popScene();
    
    
    /** Runnable Overrides **/
    void run(unsigned dtime) override;
};

} // namespace zge
