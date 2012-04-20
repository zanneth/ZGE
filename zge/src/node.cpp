/*
 * node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/node.h"
#include "zge/logger.h"
#include <iostream>

namespace zge {

ZNode::~ZNode()
{
    std::cout << "Node 0x" << this << " destroyed" << std::endl;
}

void ZNode::addChild(ZNodeRef node)
{
    try {
        node->_parent = shared_from_this();
    } catch (std::bad_weak_ptr exception) {
        ZLogger::warn("(ZNode::addChild) No shared pointer for parent found.");
    }
    
    _children.push_back(node);
}

bool ZNode::removeChild(ZNodeRef node)
{
    for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
        if (*itr == node) {
            _children.erase(itr);
            return true;
        }
    }
    
    return false;
}

} // namespace zge
