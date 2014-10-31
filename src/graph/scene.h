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

ZGE_BEGIN_NAMESPACE

class ZScene : public ZNode {
public:
    ZScene();
    ZScene(const ZScene &) = default;
    ~ZScene();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZScene);
    
private:
    void _evict_scene(ZNode *curnode);
    
public:
    friend class ZRenderManager;
};

ZGE_DEFINE_SREF_TYPE(ZScene);

ZGE_END_NAMESPACE
