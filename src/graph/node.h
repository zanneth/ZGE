/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/foundation.h>
#include <zge/action.h>
#include <zge/geometry.h>
#include <zge/render_context.h>

BEGIN_ZGE_NAMESPACE

class ZScene;

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode : public std::enable_shared_from_this<ZNode> {
protected:
    unsigned     _uid;
    ZVector      _position;
    ZMatrix      _transform;
    ZMatrix      _pos_transform;
    std::string  _name;
    ZGeometryRef _geometry;
    
    ZNode   *_parent; // weak
    ZScene  *_scene; // weak
    
    std::vector<ZNodeRef>   _children;
    std::vector<ZActionRef> _actions;
    
public:
    ZNode(ZGeometryRef geometry = nullptr);
    ZNode(const ZNode&) = default;
    virtual ~ZNode();
    
    /* Operators */
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /* Accessors */
    ZNode*   get_parent();
    ZScene*  get_scene();
    
    std::string get_name() const;
    void        set_name(const std::string &name);
    
    virtual ZVector get_position();
    virtual void    set_position(const ZVector &position);
    
    virtual ZMatrix get_transform();
    virtual void    set_transform(const ZMatrix &transform);
    
    ZGeometryRef get_geometry() const;
    void         set_geometry(ZGeometryRef geometry);
    
    /* Manipulating Geometry */
    void append_transform(const ZMatrix &transform);
    
    /* Managing Sub-Nodes */
    virtual void add_child(ZNodeRef node);
    virtual bool remove_child(ZNodeRef node);
    
    void remove_from_parent();
    std::vector<ZNodeRef> get_children();
    
    /* Description */
    virtual std::string get_description();
    
    /* Actions */
    void add_action(ZActionRef action);
    void remove_action(ZActionRef action);
    void remove_all_actions();
    
    /* Callbacks */
    virtual void on_enter() {}
    virtual void on_exit() {}
    
protected:
    virtual void _draw(ZRenderContextRef context);
    virtual void _update();

private:
    void _remove_child_uid(unsigned uid);
    void _on_enter_internal();
    void _on_exit_internal();
    
public:
    friend class ZScene;
};

END_ZGE_NAMESPACE
