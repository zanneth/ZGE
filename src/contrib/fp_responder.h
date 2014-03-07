/*
 * fp_responder.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/21/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/noncopyable.h>
#include <zge/input_manager.h>
#include <zge/scene.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZFirstPersonResponder> ZFirstPersonResponderRef;

class ZFirstPersonResponder : public ZResponder, ZNoncopyable {
    std::weak_ptr<ZScene> _scene;
    float _mouse_speed; // 0.0 - 1.0
    
public:
    ZFirstPersonResponder();
    ~ZFirstPersonResponder() {}
    
    /* Responder Overrides */
    void set_function(const ZResponderFunction&) override {}
    
    /* Accessors */
    ZSceneRef get_scene() { return _scene.lock(); }
    void set_scene(ZSceneRef scene) { _scene = scene; }
    float get_mouse_speed() { return _mouse_speed; }
    void set_mouse_speed(float speed) { _mouse_speed = speed; }
    
private:
    void _responder_function(const ZEvent &event);
};

END_ZGE_NAMESPACE
