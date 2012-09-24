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

typedef std::shared_ptr<class node> node_ref;
class scene;

class node {
protected:
    uid _id;
    vec3 _position;
    
    node *_parent; // weak
    scene *_scene; // weak
    std::vector<node_ref> _children;
    
public:
    node();
    node(const node&) = default;
    ~node();
    
    /** Operators **/
    bool operator==(const node &other);
    bool operator!=(const node &other);
    
    /** Accessors **/
    node* get_parent() { return _parent; }
    scene* get_scene() { return _scene; }
    vec3 get_position() { return _position; }
    void set_position(const vec3 &position) { _position = position; }
    
    /** Managing Sub-Nodes **/
    virtual void add_child(node_ref node);
    virtual bool remove_child(node_ref node);
    virtual std::vector<node_ref> get_children() { return _children; }
    
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
    friend class game_manager;
    friend class scene;
};

} // namespace zge
