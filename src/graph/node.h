/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/geometry.h>
#include <zge/render_context.h>
#include <memory>
#include <string>
#include <vector>

BEGIN_ZGE_NAMESPACE

class ZScene;

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode {
protected:
    unsigned     _uid;
    ZVector      _position;
    ZMatrix      _transform;
    ZMatrix      _pos_transform;
    std::string  _name;
    ZGeometryRef _geometry;
    
    ZNode   *_parent; // weak
    ZScene  *_scene; // weak
    std::vector<ZNodeRef> _children;
    
public:
    ZNode(ZGeometryRef geometry = nullptr);
    ZNode(const ZNode&) = default;
    virtual ~ZNode();
    
    /* Operators */
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /* Accessors */
    ZNode*   get_parent() { return _parent; }
    ZScene*  get_scene() { return _scene; }
    
    std::string get_name() const { return _name; }
    void        set_name(const std::string &name) { _name = name; }
    
    virtual ZVector get_position() { return _position; }
    virtual void    set_position(const ZVector &position);
    
    virtual ZMatrix get_transform() { return _transform; }
    virtual void    set_transform(const ZMatrix &transform) { _transform = transform; }
    
    ZGeometryRef get_geometry() const { return _geometry; }
    void         set_geometry(ZGeometryRef geometry) { _geometry = geometry; }
    
    /* Manipulating Geometry */
    void append_transform(const ZMatrix &transform);
    
    /* Managing Sub-Nodes */
    virtual void add_child(ZNodeRef node);
    virtual bool remove_child(ZNodeRef node);
    
    void remove_from_parent();
    std::vector<ZNodeRef> get_children() { return _children; }
    
    /* Description */
    virtual std::string get_description();
    
    /* Callbacks */
    virtual void on_enter() {}
    virtual void on_exit() {}
    
protected:
    virtual void _draw(ZRenderContextRef context);

private:
    void _remove_child_uid(unsigned uid);
    void _on_enter_internal();
    void _on_exit_internal();
    
public:
    friend class ZSceneManager;
    friend class ZScene;
};

END_ZGE_NAMESPACE
