/*
 * scene.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include <zge/scene.h>
#include <zge/light.h>
#include <zge/logger.h>
#include <typeinfo>

BEGIN_ZGE_NAMESPACE

ZScene::ZScene() : ZNode(),
    _active_camera(nullptr)
{
    _scene = this;
    set_position({0.0, 0.0, 0.0});
}

ZScene::~ZScene()
{
    _evict_scene(this);
}

#pragma mark - Node Overrides

void ZScene::add_child(ZNodeRef node)
{
    if (auto cam = std::dynamic_pointer_cast<ZCamera>(node)) {
        _active_camera = cam;
        ZLogger::log("Camera %p added to scene.", _active_camera.get());
    }
    
    ZNode::add_child(node);
}

void ZScene::_draw(ZRenderContextRef context)
{
    _prepare_camera(context);
    _prepare_lights(context);
    
    ZNode::_draw(context);
    
    _teardown_camera(context);
    _teardown_lights(context);
}

#pragma mark - Private

void ZScene::_evict_scene(ZNode *curnode)
{
    curnode->_scene = nullptr;
    for (ZNodeRef node : curnode->_children) {
        _evict_scene(node.get());
    }
}

void ZScene::_prepare_camera(ZRenderContextRef context)
{
    if (_active_camera) {
        _active_camera->open(context);
    }
}

void ZScene::_prepare_lights(ZRenderContextRef context)
{
    std::vector<ZLightRef> lights;
    for (ZNodeRef child : _children) {
        ZLightRef light = std::dynamic_pointer_cast<ZLight>(child);
        if (light) {
            lights.push_back(light);
        }
    }
    context->add_lights(lights);
}

void ZScene::_teardown_camera(ZRenderContextRef context)
{
    if (_active_camera) {
        _active_camera->close();
    }
}

void ZScene::_teardown_lights(ZRenderContextRef context)
{
    context->clear_lights();
}

END_ZGE_NAMESPACE
