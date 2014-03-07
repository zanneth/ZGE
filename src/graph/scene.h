/*
 * scene.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#pragma once

#include <zge/camera.h>
#include <zge/defines.h>
#include <zge/node.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZScene> ZSceneRef;

class ZScene : public ZNode {
    ZCameraRef _active_camera;
    
public:
    ZScene();
    ZScene(const ZScene &) = default;
    ~ZScene();
    
    /* Accessors */
    ZCameraRef get_active_camera() { return _active_camera; }
    
    /* Node Overrides */
    void add_child(ZNodeRef node) override;

protected:
    void _draw(ZRenderContextRef context) override;
    
private:
    void _evict_scene(ZNode *curnode);
    
public:
    friend class ZSceneManager;
    friend class ZRenderManager;
};

END_ZGE_NAMESPACE
