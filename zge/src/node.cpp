/*
 * node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/node.h"
#include "zge/logger.h"
#include <iostream>
#include <algorithm>

namespace zge {

ZNode::~ZNode()
{
    ZLogger::log("Node 0x%x destroyed", this);
}


#pragma mark - Managing Children

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
    auto itr = std::find(_children.begin(), _children.end(), node);
    if (itr != _children.end()) {
        _children.erase(itr);
        return true;
    }
    
    return false;
}

} // namespace zge
