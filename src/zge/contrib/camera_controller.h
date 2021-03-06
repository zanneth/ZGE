/*
 * camera_controller.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/23/2014
 */

#pragma once

#include <zge/core/foundation.h>
#include <zge/contrib/3dcamera.h>
#include <zge/input/responder.h>

ZGE_BEGIN_NAMESPACE

class ZCameraController : public ZResponder {
public:
    ZCameraController(Z3DCameraRef camera = nullptr);
    ~ZCameraController() = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZCameraController);
    
    Z3DCameraRef get_camera() const;
    void set_camera(Z3DCameraRef camera);
    
    float get_movement_speed() const;
    void set_movement_speed(float speed);
    
private:
    void _receive_event(const ZEvent &event);
    
private:
    Z3DCameraRef _camera;
    float _movement_speed;
};

ZGE_DEFINE_SREF_TYPE(ZCameraController);

ZGE_END_NAMESPACE
