/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/geometry.h"
#include "zge/types.h"

#include <memory>
#include <vector>

namespace zge {

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode {
protected:
    ZUUID _uuid;
    ZVecf _position;
    ZMatrixf _transformMatrix;
    
    ZNode *_parent;
    std::vector<ZNodeRef> _children;
    
public:
    ZNode();
    ZNode(const ZNode &node) = default;
    ~ZNode();
    
    /** Operators **/
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /** Accessors **/
    ZNode* getParent() const { return _parent; }
    ZVecf getPosition() const { return _position; }
    void setPosition(const ZVecf &position) { _position = position; }
    
    /** Managing Sub-Nodes **/
    void addChild(ZNodeRef node);
    bool removeChild(ZNodeRef node);
    
    /** Updating **/
    virtual void update(unsigned dtime) {}
};

} // namespace zge
