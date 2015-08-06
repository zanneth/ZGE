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

ZGE_FORWARD_DECLARE_SREF(ZRenderContext);

ZGE_BEGIN_NAMESPACE

class ZScene : public ZNode {
public:
    ZScene();
    ZScene(const ZScene &) = default;
    ~ZScene();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZScene);
    
    void update() override;
    void handle_input_event(const ZEvent &event) override;
    void draw(ZRenderContextRef context);
    
private:
    void _evict_scene(ZNode *curnode);
    
private:
    bool _update_reentr;
    bool _handle_input_reentr;
};

ZGE_DEFINE_SREF_TYPE(ZScene);

ZGE_END_NAMESPACE
