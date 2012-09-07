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

ZNode::ZNode() :
    _parent(nullptr),
    _scene(nullptr)
{}

ZNode::~ZNode()
{
    ZLogger::log("%s destroyed", getDescription().c_str());
}


#pragma mark - Operators

bool ZNode::operator==(const ZNode &other)
{
    return _uuid == other._uuid;
}

bool ZNode::operator!=(const ZNode &other)
{
    return !operator==(other);
}


#pragma mark - Managing Children

void ZNode::addChild(ZNodeRef node)
{
    node->_scene  = _scene;
    node->_parent = this;
    
    _children.push_back(node);
    node->_onEnterInternal();
}

bool ZNode::removeChild(ZNodeRef node)
{
    for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
        if (**itr == *node) {
            node->_scene    = nullptr;
            node->_parent   = nullptr;
            
            _children.erase(itr);
            node->_onExitInternal();
            
            return true;
        }
    }
    
    return false;
}


#pragma mark - Description

std::string ZNode::getDescription()
{
    std::ostringstream oss;
    oss << "Node (" << this << ") #" << _uuid.getDescription();
    
    return oss.str();
}


#pragma mark - Private

void ZNode::_updateInternal(unsigned dtime)
{
    update(dtime);
    
    for (ZNodeRef child : _children) {
        child->_updateInternal(dtime);
    }
}

void ZNode::_drawInternal()
{
    draw();
    
    for (ZNodeRef child : _children) {
        child->_drawInternal();
    }
}

void ZNode::_onEnterInternal()
{
    onEnter();
    
    for (ZNodeRef child : _children) {
        child->_onEnterInternal();
    }
}

void ZNode::_onExitInternal()
{
    onExit();
    
    for (ZNodeRef child : _children) {
        child->_onExitInternal();
    }
}

} // namespace zge
