//
//  node.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/9/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/node.h"
#include "zge/logger.h"
#include <iostream>

namespace zge {

ZNode::~ZNode()
{
    std::cout << "Node 0x" << this << " destroyed" << std::endl;
}

void ZNode::addChild(shared_ptr<ZNode> node)
{
    try {
        node->_parent = shared_from_this();
    } catch (std::bad_weak_ptr exception) {
        ZLogger::warn("(ZNode::addChild) No shared pointer for parent found.");
    }
    
    _children.push_back(node);
}

bool ZNode::removeChild(shared_ptr<ZNode> node)
{
    for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
        if (*itr == node) {
            _children.erase(itr);
            return true;
        }
    }
    
    return false;
}

}
