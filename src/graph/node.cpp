/*
 * node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/node.h>
#include <zge/logger.h>

#include <sstream>
#include <typeinfo>

static unsigned __node_global_uid_count = 1;

namespace zge {

ZNode::ZNode() :
    _uid(__node_global_uid_count++),
    _position(0.0, 0.0, 0.0),
    _transform(Affine3f::Identity()),
    _parent(nullptr),
    _scene(nullptr),
    _pos_transform(Affine3f::Identity())
{}

ZNode::~ZNode()
{
#if (ZDEBUG)
    ZLogger::log("%s destroyed", get_description().c_str());
#endif
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

#pragma mark - Accessors

void ZNode::set_position(const Vector3f &position)
{
    _position = position;
    _pos_transform = Eigen::Translation3f(position);
}

#pragma mark - Manipulating Geometry

void ZNode::append_transform(const Affine3f &transform)
{
    _transform = _transform * transform;
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

void ZNode::remove_from_parent()
{
    _parent->_remove_child_uid(_uid);
}

#pragma mark - Description

std::string ZNode::get_description()
{
    std::ostringstream oss;
    oss << "Node (" << this << ") #" << _uid;
    
    return oss.str();
}

#pragma mark - Private

void ZNode::_update_internal(uint32_t dtime)
{
    update(dtime);
    
    for (ZNodeRef child : _children) {
        child->_update_internal(dtime);
    }
}

void ZNode::_draw_internal(ZRenderContextRef context)
{
    before_draw(context);
    
    draw(context);
    
    for (ZNodeRef child : _children) {
        child->_draw_internal(context);
    }
    
    after_draw(context);
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

void ZNode::_remove_child_uid(unsigned uid)
{
    auto child = std::find_if(_children.begin(), _children.end(), [uid](ZNodeRef child) { return child->_uid == uid; });
    if (child != _children.end()) {
        ZNodeRef node = *child;
        node->_scene  = nullptr;
        node->_parent = nullptr;

        _children.erase(child);
        node->_on_exit_internal();
   }
}

} // namespace zge
