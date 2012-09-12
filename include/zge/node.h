/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/types.h"
#include "zge/vector.h"

#include <memory>
#include <string>
#include <vector>

namespace zge {

typedef std::shared_ptr<class ZNode> ZNodeRef;
class ZScene;

class ZNode {
protected:
    ZUID _id;
    ZVec3 _position;
    
    ZNode *_parent; // weak
    ZScene *_scene; // weak
    std::vector<ZNodeRef> _children;
    
public:
    ZNode();
    ZNode(const ZNode&) = default;
    ~ZNode();
    
    /** Operators **/
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /** Accessors **/
    ZNode* getParent() { return _parent; }
    ZScene* getScene() { return _scene; }
    ZVec3 getPosition() { return _position; }
    void setPosition(const ZVec3 &position) { _position = position; }
    
    /** Managing Sub-Nodes **/
    virtual void addChild(ZNodeRef node);
    virtual bool removeChild(ZNodeRef node);
    virtual std::vector<ZNodeRef> getChildren() { return _children; }
    
    /** Description **/
    virtual std::string getDescription();
    
    /** Updating **/
    virtual void update(unsigned dtime) {}
    
    /** Drawing **/
    virtual void draw() {}
    
    /** Callbacks **/
    virtual void onEnter() {}
    virtual void onExit() {}
    
protected:
    virtual void _updateInternal(unsigned dtime);
    virtual void _drawInternal();
    virtual void _onEnterInternal();
    virtual void _onExitInternal();
    
public:
    friend class ZGameManager;
    friend class ZScene;
};

} // namespace zge
