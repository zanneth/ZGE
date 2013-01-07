/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/geometry.h"
#include "zge/model.h"

#include <memory>
#include <string>
#include <vector>

namespace zge {

class ZScene;

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode {
protected:
    unsigned _uid;
    ZVec3 _position;
    ZVec3 _velocity;
    ZAffine3 _transform;
    
    ZNode *_parent; // weak
    ZScene *_scene; // weak
    std::vector<ZNodeRef> _children;
    
    ZModelRef _model;
    
private:
    ZAffine3 _pos_transform;
    
public:
    ZNode();
    ZNode(const ZNode&) = default;
    virtual ~ZNode();
    
    /** Operators **/
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /** Accessors **/
    ZNode* get_parent() { return _parent; }
    ZScene* get_scene() { return _scene; }
    ZVec3 get_position() { return _position; }
    void set_position(const ZVec3 &position);
    ZVec3 get_velocity() { return _velocity; }
    void set_velocity(const ZVec3 &velocity) { _velocity = velocity; }
    
    virtual ZAffine3 get_transform() { return _transform; }
    virtual void set_transform(const ZAffine3 &transform) { _transform = transform; }
    virtual ZModelRef get_model() { return _model; }
    virtual void set_model(ZModelRef model) { _model = model; }
    
    /** Manipulating Geometry **/
    void append_transform(const ZAffine3 &transform);
    
    /** Managing Sub-Nodes **/
    virtual void add_child(ZNodeRef node);
    virtual bool remove_child(ZNodeRef node);
    virtual std::vector<ZNodeRef> get_children() { return _children; }
    virtual void remove_from_parent();
    
    /** Description **/
    virtual std::string get_description();
    
    /** Updating **/
    virtual void update(uint32_t dtime);
    
    /** Drawing **/
    virtual void before_draw() {}
    virtual void after_draw() {}
    
    /** Callbacks **/
    virtual void on_enter() {}
    virtual void on_exit() {}
    
protected:
    virtual void _update_internal(uint32_t dtime);
    virtual void _draw_internal();
    virtual void _on_enter_internal();
    virtual void _on_exit_internal();

private:
    void _remove_child_uid(unsigned uid);
    
public:
    friend class ZGameManager;
    friend class ZScene;
};

} // namespace zge
