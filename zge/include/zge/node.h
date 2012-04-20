/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/geometry.h"

#include <memory>
#include <vector>

namespace zge {

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode : public std::enable_shared_from_this<ZNode> {
    ZVecf _position;
    
    std::vector<ZNodeRef> _children;
    std::weak_ptr<ZNode> _parent;
    
public:
    ~ZNode();
    
    /** Accessors **/
    ZVecf getPosition() const { return _position; }
    void setPosition(const ZVecf &position) { _position = position; }
    ZNodeRef getParent() const { return _parent.lock(); }
    
    
    /** Managing Sub-Nodes **/
    void addChild(ZNodeRef node);
    bool removeChild(ZNodeRef node);
    
    
    /** Updating **/
    virtual void update(unsigned dtime) {}
};

} // namespace zge
