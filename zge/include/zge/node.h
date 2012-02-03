//
//  node.h
//  ZGE
//
//  Created by Charles Magahern on 1/9/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/geometry.h"

#include <memory>
#include <vector>

namespace zge {

using std::shared_ptr;
using std::weak_ptr;
using std::vector;

typedef shared_ptr<class ZNode> ZNodeRef;

class ZNode : public std::enable_shared_from_this<ZNode> {
    ZVecf _position;
    
    vector<ZNodeRef> _children;
    weak_ptr<ZNode> _parent;
    
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