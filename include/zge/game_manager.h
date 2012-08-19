/*
 * game_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include "zge/node.h"
#include "zge/schedulable.h"
#include "zge/scene.h"

#include <memory>
#include <stack>

namespace zge {

typedef std::shared_ptr<class ZGameManager> ZGameManagerRef;

class ZGameManager : public ZSchedulable, ZNonCopyable {
    std::stack<ZSceneRef> _sceneStack;
    
public:
    /** Scene Management **/
    ZSceneRef getCurrentScene();
    void pushScene(ZSceneRef scene);
    ZSceneRef popScene();
    
    /** ZSchedulable **/
    void run(unsigned dtime) override;
};

} // namespace zge
