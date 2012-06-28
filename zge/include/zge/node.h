/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/types.h"

#include <memory>
#include <vector>

namespace zge {

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode {
protected:
    ZUUID _uuid;
    
    ZNode *_parent;
    std::vector<ZNodeRef> _children;
    
public:
    ZNode();
    ZNode(const ZNode&) = default;
    ~ZNode();
    
    /** Operators **/
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /** Accessors **/
    ZNode* getParent() const { return _parent; }
    
    /** Managing Sub-Nodes **/
    void addChild(ZNodeRef node);
    bool removeChild(ZNodeRef node);
    
    /** Updating **/
    virtual void update(unsigned dtime) {}
};

} // namespace zge
