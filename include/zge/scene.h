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

namespace zge {

typedef std::shared_ptr<class ZScene> ZSceneRef;

class ZScene : public ZNode {
    ZCameraRef _active_camera;
    ZViewport _viewport;
    
public:
    ZScene();
    ZScene(const ZScene &) = default;
    ~ZScene();
    
    /** Accessors **/
    ZCameraRef get_active_camera() { return _active_camera; }
    ZViewport get_viewport() { return _viewport; }
    void set_viewport(const ZViewport &vp) { _viewport = vp; }
    
    /** Node Overrides **/
    void add_child(ZNodeRef node) override;
    
private:
    void _draw_internal() override;
    void _evict_scene(ZNode *curnode);
    
public:
    friend class ZGameManager;
};

} // namespace zge
