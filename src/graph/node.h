/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/geometry.h>
#include <zge/model.h>
#include <zge/render_context.h>

#include <memory>
#include <string>
#include <vector>

namespace zge {

class ZScene;

typedef std::shared_ptr<class ZNode> ZNodeRef;

class ZNode {
protected:
    unsigned _uid;
    Vector3f _position;
    Affine3f _transform;
    
    ZNode   *_parent; // weak
    ZScene  *_scene; // weak
    std::vector<ZNodeRef> _children;
    
private:
    Affine3f _pos_transform;
    
public:
    ZNode();
    ZNode(const ZNode&) = default;
    virtual ~ZNode();
    
    /* Operators */
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /* Accessors */
    ZNode* get_parent() { return _parent; }
    ZScene* get_scene() { return _scene; }
    Vector3f get_position() { return _position; }
    void set_position(const Vector3f &position);
    
    virtual Affine3f get_transform() { return _transform; }
    virtual void set_transform(const Affine3f &transform) { _transform = transform; }
    
    /* Manipulating Geometry */
    void append_transform(const Affine3f &transform);
    
    /* Managing Sub-Nodes */
    virtual void add_child(ZNodeRef node);
    virtual bool remove_child(ZNodeRef node);
    virtual std::vector<ZNodeRef> get_children() { return _children; }
    virtual void remove_from_parent();
    
    /* Description */
    virtual std::string get_description();
    
    /* Updating */
    virtual void update(uint32_t dtime) {}
    
    /* Drawing */
    virtual void before_draw(ZRenderContextRef context) {}
    virtual void draw(ZRenderContextRef context) {}
    virtual void after_draw(ZRenderContextRef context) {}
    
    /* Callbacks */
    virtual void on_enter() {}
    virtual void on_exit() {}
    
protected:
    void _update_internal(uint32_t dtime);
    void _draw_internal(ZRenderContextRef context);
    void _on_enter_internal();
    void _on_exit_internal();

private:
    void _remove_child_uid(unsigned uid);
    
public:
    friend class ZSceneManager;
    friend class ZScene;
};

} // namespace zge
