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
public:
    ZScene();
    ZScene(const ZScene &) = default;
    ~ZScene();
    
private:
    void _evict_scene(ZNode *curnode);
    
public:
    friend class ZRenderManager;
};

END_ZGE_NAMESPACE
