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

typedef std::shared_ptr<class ZScene> ZSceneRef;

class ZScene : public ZNode {
    ZCameraRef _activeCamera;
    ZViewport _viewport;
    
public:
    ZScene();
    ZScene(const ZScene &) = default;
    ~ZScene();
    
    /** Accessors **/
    ZCameraRef getActiveCamera() { return _activeCamera; }
    ZViewport getViewport() { return _viewport; }
    void setViewport(const ZViewport &vp) { _viewport = vp; }
    
    /** Node Overrides **/
    void addChild(ZNodeRef node) override;
    
private:
    void _drawInternal() override;
    void _evictScene(ZNode *curnode);
    
public:
    friend class ZGameManager;
};

} // namespace zge
