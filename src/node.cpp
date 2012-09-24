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

namespace zge {

node::node() :
    _parent(nullptr),
    _scene(nullptr)
{}

node::~node()
{
    logger::log("%s destroyed", get_description().c_str());
}


#pragma mark - Operators

bool node::operator==(const node &other)
{
    return _id == other._id;
}

bool node::operator!=(const node &other)
{
    return !operator==(other);
}


#pragma mark - Managing Children

void node::add_child(node_ref node)
{
    node->_scene  = _scene;
    node->_parent = this;
    
    _children.push_back(node);
    node->_on_enter_internal();
}

bool node::remove_child(node_ref node)
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

std::string node::get_description()
{
    std::ostringstream oss;
    oss << "Node (" << this << ") #" << _id.get_description();
    
    return oss.str();
}


#pragma mark - Private

void node::_update_internal(unsigned dtime)
{
    update(dtime);
    
    for (node_ref child : _children) {
        child->_update_internal(dtime);
    }
}

void node::_draw_internal()
{
    draw();
    
    for (node_ref child : _children) {
        child->_draw_internal();
    }
}

void node::_on_enter_internal()
{
    on_enter();
    
    for (node_ref child : _children) {
        child->_on_enter_internal();
    }
}

void node::_on_exit_internal()
{
    on_exit();
    
    for (node_ref child : _children) {
        child->_on_exit_internal();
    }
}

} // namespace zge
