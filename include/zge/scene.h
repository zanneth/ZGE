/*
 * scene.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#pragma once

#include "zge/camera.h"
#include "zge/node.h"
#include "zge/viewport.h"

#include <memory>

namespace zge {

typedef std::shared_ptr<class scene> scene_ref;

class scene : public node {
    camera_ref _active_camera;
    viewport _viewport;
    
public:
    scene();
    scene(const scene &) = default;
    ~scene();
    
    /** Accessors **/
    camera_ref get_active_camera() { return _active_camera; }
    viewport get_viewport() { return _viewport; }
    void set_viewport(const viewport &vp) { _viewport = vp; }
    
    /** Node Overrides **/
    void add_child(node_ref node) override;
    
private:
    void _draw_internal() override;
    void _evict_scene(node *curnode);
    
public:
    friend class game_manager;
};

} // namespace zge
