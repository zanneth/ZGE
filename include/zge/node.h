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

class ZScene;

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode {
protected:
    ZUID _id;
    vec3 _position;
    
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
    ZNode* get_parent() { return _parent; }
    ZScene* get_scene() { return _scene; }
    vec3 get_position() { return _position; }
    void set_position(const vec3 &position) { _position = position; }
    
    /** Managing Sub-Nodes **/
    virtual void add_child(ZNodeRef node);
    virtual bool remove_child(ZNodeRef node);
    virtual std::vector<ZNodeRef> get_children() { return _children; }
    
    /** Description **/
    virtual std::string get_description();
    
    /** Updating **/
    virtual void update(unsigned dtime) {}
    
    /** Drawing **/
    virtual void draw() {}
    
    /** Callbacks **/
    virtual void on_enter() {}
    virtual void on_exit() {}
    
protected:
    virtual void _update_internal(unsigned dtime);
    virtual void _draw_internal();
    virtual void _on_enter_internal();
    virtual void _on_exit_internal();
    
public:
    friend class ZGameManager;
    friend class ZScene;
};

} // namespace zge
