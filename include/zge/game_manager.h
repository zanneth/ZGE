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

typedef std::shared_ptr<class game_manager> game_manager_ref;

class game_manager : public schedulable, noncopyable {
    std::stack<scene_ref> _scene_stack;
    
public:
    /** Scene Management **/
    scene_ref get_current_scene();
    void push_scene(scene_ref scene);
    scene_ref pop_scene();
    
    /** schedulable **/
    void run(unsigned dtime) override;
};

} // namespace zge
