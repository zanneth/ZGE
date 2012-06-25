/*
 * game_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include "zge/node.h"
#include "zge/runnable_interface.h"
#include "zge/scene.h"

#include <memory>
#include <stack>

namespace zge {

typedef std::shared_ptr<class ZGameManager> ZGameManagerRef;

class ZGameManager : public ZRunnableInterface, ZNonCopyable {
    std::stack<ZSceneRef> _sceneStack;
    
public:
    /** Scene Management **/
    ZSceneRef getCurrentScene() const;
    void pushScene(ZSceneRef scene);
    ZSceneRef popScene();
    
    /** Runnable Overrides **/
    void run(unsigned dtime) override;
};

} // namespace zge
