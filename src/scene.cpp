/*
 * scene.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include "zge/scene.h"
#include "zge/logger.h"
#include "zge/vector.h"

#include <typeinfo>

namespace zge {

scene::scene() : node(),
    _active_camera(nullptr)
{
    _scene = this;
    set_position(vec3(0.0, 0.0, 0.0));
}

scene::~scene()
{
    _evict_scene(this);
}


#pragma mark - Node Overrides

void scene::add_child(node_ref node)
{
    if (auto cam = std::dynamic_pointer_cast<camera>(node)) {
        _active_camera = cam;
        logger::log("Camera 0x%x added to scene.", _active_camera.get());
    }
    
    node::add_child(node);
}

void scene::_draw_internal()
{
    if (_active_camera.get() == nullptr) {
        return;
    }
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    _viewport.open();
    _active_camera->open();
    
    node::_draw_internal();
    
    _active_camera->close();
    _viewport.close();
}


#pragma mark - Private

void scene::_evict_scene(node *curnode)
{
    curnode->_scene = nullptr;
    for (node_ref node : curnode->_children) {
        _evict_scene(node.get());
    }
}

} // namespace zge
