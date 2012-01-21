//
//  node.h
//  ZGE
//
//  Created by Charles Magahern on 1/9/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_NODE_H_
#define _ZGE_NODE_H_

#include <memory>
#include <vector>
#include <zge/common/geometry.h>

namespace zge {
using std::shared_ptr;
using std::weak_ptr;
using std::vector;

class ZNode : public std::enable_shared_from_this<ZNode> {
    ZPoint _position;
    
    vector<shared_ptr<ZNode>> _children;
    weak_ptr<ZNode> _parent;
    
public:
    ~ZNode();
    
    /** Accessors **/
    ZPoint getPosition() const { return _position; }
    void setPosition(const ZPoint &position) { _position = position; }
    shared_ptr<ZNode> getParent() const { return _parent.lock(); }
    
    
    /** Managing Sub-Nodes **/
    void addChild(shared_ptr<ZNode> node);
    bool removeChild(shared_ptr<ZNode> node);
    
    
    /** Updating **/
    virtual void update(unsigned dtime) {}
};

}

#endif // _ZGE_NODE_H_
