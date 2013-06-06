/*
 * game_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/noncopyable.h>
#include <zge/node.h>
#include <zge/schedulable.h>
#include <zge/scene.h>

#include <memory>
#include <stack>

namespace zge {

class ZGameManager : public ZSchedulable, ZNoncopyable {
    std::stack<ZSceneRef> _scene_stack;
    
public:
    /* Scene Management */
    ZSceneRef get_current_scene();
    void push_scene(ZSceneRef scene);
    ZSceneRef pop_scene();
    
    /* schedulable */
    void run(uint32_t dtime) override;
};

typedef std::shared_ptr<ZGameManager> ZGameManagerRef;

} // namespace zge
