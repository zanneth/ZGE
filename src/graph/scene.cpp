/*
 * scene.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include <zge/scene.h>
#include <zge/logger.h>

#include <typeinfo>

namespace zge {

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

void ZScene::before_draw(ZRenderContextRef context)
{
    if (_active_camera.get() != nullptr) {
        _active_camera->open(context);
    }
}

void ZScene::after_draw(ZRenderContextRef context)
{
    if (_active_camera.get() != nullptr) {
        _active_camera->close();
    }
}

#pragma mark - Private

void ZScene::_evict_scene(ZNode *curnode)
{
    curnode->_scene = nullptr;
    for (ZNodeRef node : curnode->_children) {
        _evict_scene(node.get());
    }
}

} // namespace zge
