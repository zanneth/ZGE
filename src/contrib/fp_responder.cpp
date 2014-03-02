/*
 * fp_responder.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/21/2012
 */
 
#include <zge/fp_responder.h>
#include <zge/logger.h>
#include <zge/scene.h>

#include <cmath>
#include <functional>

#define DEFAULT_MOUSE_SPEED 0.0005f // TODO: this shouldn't be so arbitrary

BEGIN_ZGE_NAMESPACE

ZFirstPersonResponder::ZFirstPersonResponder() : ZResponder(),
    _mouse_speed(DEFAULT_MOUSE_SPEED)
{
    _function = std::bind(&ZFirstPersonResponder::_responder_function, this, std::placeholders::_1);
}

void ZFirstPersonResponder::_responder_function(const ZEvent &event)
{
    ZSceneRef scene = _scene.lock();
    if (scene.get() != nullptr) {
        ZCameraRef camera = scene->get_active_camera();
        
        if (event.type == ZMOUSE_MOVED_EVENT) {
            ZMouseEvent mouse_event = event.mouse_event;
            float dx = mouse_event.velocity.x * _mouse_speed;
            float dy = mouse_event.velocity.y * _mouse_speed;
            
            ZMatrix rotation;
            rotation.rotate(-dx, 1.0, 0.0, 0.0);
            rotation.rotate(-dy, 0.0, 1.0, 0.0);
            
            camera->set_transform(rotation);
        } else if (event.type == ZKEY_DOWN_EVENT || event.type == ZKEY_UP_EVENT) {
            ZKeyEvent key_event = event.key_event;
            ZVector movement_vector;
            switch (key_event.key) {
                case ZKEY_W:
                    movement_vector = { 0.0, 0.0, -1.0 };
                    break;
                case ZKEY_A:
                    movement_vector = { -1.0, 0.0, 0.0 };
                    break;
                case ZKEY_S:
                    movement_vector = { 0.0, 0.0, 1.0 };
                    break;
                case ZKEY_D:
                    movement_vector = { 1.0, 0.0, 0.0 };
                    break;
                default:
                    break;
            }
            const float scalar = 0.05f;
            movement_vector = movement_vector * scalar;
        }
    }
}

END_ZGE_NAMESPACE
