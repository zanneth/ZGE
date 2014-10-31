/*
 * camera_controller.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/23/2014
 */

#include "camera_controller.h"
#include "vector.h"

ZGE_BEGIN_NAMESPACE

ZCameraController::ZCameraController(Z3DCameraRef camera) :
    ZResponder([this] (const ZEvent &e) { _receive_event(e); }),
    _camera(camera),
    _movement_speed(1.0)
{}

#pragma mark - Accessors

Z3DCameraRef ZCameraController::get_camera() const { return _camera; }

void ZCameraController::set_camera(Z3DCameraRef camera) { _camera = camera; }

float ZCameraController::get_movement_speed() const { return _movement_speed; }

void ZCameraController::set_movement_speed(float speed) { _movement_speed = speed; }

#pragma mark - Internal

void ZCameraController::_receive_event(const ZEvent &event)
{
    if (!_camera) {
        return;
    }
    
    if (event.type == ZEventType::ZKEY_DOWN_EVENT) {
        ZKeyEvent key_event = event.key_event;
        ZVector pos_delta = ZVector::zero;
        ZVector look_delta = ZVector::zero;
        
        switch (key_event.key) {
            case ZKEY_UP:
                pos_delta = { 0.0, 1.0, 0.0 };
                break;
            case ZKEY_DOWN:
                pos_delta = { 0.0, -1.0, 0.0 };
                break;
            case ZKEY_LEFT:
                pos_delta = { -1.0, 0.0, 0.0 };
                break;
            case ZKEY_RIGHT:
                pos_delta = { 1.0, 0.0, 0.0 };
                break;
            case ZKEY_PLUS:
            case ZKEY_EQUALS:
                pos_delta = { 0.0, 0.0, -1.0 };
                look_delta = { 0.0, 0.0, -1.0 };
                break;
            case ZKEY_MINUS:
                pos_delta = { 0.0, 0.0, 1.0 };
                look_delta = { 0.0, 0.0, 1.0 };
                break;
            default:
                break;
        }
        
        ZVector current_pos = _camera->get_position();
        _camera->set_position(current_pos + (pos_delta * _movement_speed));
        
        ZVector current_look = _camera->get_look();
        _camera->set_look(current_look + (look_delta * _movement_speed));
    }
}

ZGE_END_NAMESPACE
