/*
 * node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/node.h"
#include "zge/logger.h"

#include <sstream>
#include <typeinfo>

static unsigned __node_global_uid_count = 1;

namespace zge {

ZNode::ZNode() :
    _transform(ZMat4::identity()),
    _parent(nullptr),
    _scene(nullptr),
    _uid(__node_global_uid_count++)
{}

ZNode::~ZNode()
{
    ZLogger::log("%s destroyed", get_description().c_str());
}


#pragma mark - Operators

bool ZNode::operator==(const ZNode &other)
{
    return _uid == other._uid;
}

bool ZNode::operator!=(const ZNode &other)
{
    return !operator==(other);
}


#pragma mark - Manipulating Geometry

void ZNode::append_transform(const ZMat4 &transform)
{
    _transform *= transform;
}


#pragma mark - Managing Children

void ZNode::add_child(ZNodeRef node)
{
    node->_scene  = _scene;
    node->_parent = this;
    
    _children.push_back(node);
    node->_on_enter_internal();
}

bool ZNode::remove_child(ZNodeRef node)
{
    for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
        if (**itr == *node) {
            node->_scene    = nullptr;
            node->_parent   = nullptr;
            
            _children.erase(itr);
            node->_on_exit_internal();
            
            return true;
        }
    }
    
    return false;
}


#pragma mark - Description

std::string ZNode::get_description()
{
    std::ostringstream oss;
    oss << "Node (" << this << ") #" << _uid;
    
    return oss.str();
}


#pragma mark - Private

void ZNode::_update_internal(unsigned dtime)
{
    update(dtime);
    
    for (ZNodeRef child : _children) {
        child->_update_internal(dtime);
    }
}

void ZNode::_draw_internal()
{
    before_draw();
    
    if (_model) {
        glPushMatrix();
        glMultMatrixf(_transform.array);
        _model->draw();
        glPopMatrix();
    }
    
    after_draw();
    
    for (ZNodeRef child : _children) {
        child->_draw_internal();
    }
}

void ZNode::_on_enter_internal()
{
    on_enter();
    
    for (ZNodeRef child : _children) {
        child->_on_enter_internal();
    }
}

void ZNode::_on_exit_internal()
{
    on_exit();
    
    for (ZNodeRef child : _children) {
        child->_on_exit_internal();
    }
}

} // namespace zge
