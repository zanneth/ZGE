/*
 * node.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/node.h"
#include "zge/logger.h"

#include <sstream>

namespace zge {

ZNode::ZNode()
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
    node->_parent = this;
    _children.push_back(node);
}

bool ZNode::removeChild(ZNodeRef node)
{
    for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
        if (**itr == *node) {
            _children.erase(itr);
            return true;
        }
    }
    
    return false;
}


#pragma mark - Description

std::string ZNode::getDescription()
{
    std::ostringstream oss;
    oss << "ZNode (0x" << this << ") #" << _uuid.getDescription();
    
    return oss.str();
}

} // namespace zge
