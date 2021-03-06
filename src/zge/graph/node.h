/*
 * node.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/core/foundation.h>
#include <zge/graph/action.h>
#include <zge/renderer/camera.h>
#include <zge/input/event.h>
#include <zge/graph/geometry.h>
#include <zge/graph/layout.h>
#include <zge/renderer/render_context.h>
#include <zge/renderer/renderable.h>

ZGE_BEGIN_NAMESPACE

class ZLight;
class ZScene;

ZGE_FORWARD_DECLARE_SREF(ZNode);

class ZNode : public ZRenderable,
              public ZLayoutComponent,
              public std::enable_shared_from_this<ZNode>
{
public:
    ZNode(ZGeometryRef geometry = nullptr);
    ZNode(const ZNode&) = default;
    virtual ~ZNode();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZNode);
    
    /* Operators */
    bool operator==(const ZNode &other);
    bool operator!=(const ZNode &other);
    
    /* Accessors */
    ZNode*   get_parent();
    ZScene*  get_scene();
    
    std::string get_name() const;
    void        set_name(const std::string &name);
    
    virtual ZVector get_position() const;
    virtual void    set_position(const ZVector &position);
    
    virtual ZMatrix get_transform() const;
    virtual void    set_transform(const ZMatrix &transform);
    
    ZGeometryRef get_geometry() const;
    void         set_geometry(ZGeometryRef geometry);
    
    ZCameraRef get_camera() const;
    void       set_camera(ZCameraRef camera);
    
    /* Manipulating Geometry */
    void append_transform(const ZMatrix &transform);
    
    /* Managing Sub-Nodes */
    virtual void add_child(ZNodeRef node);
    virtual bool remove_child(ZNodeRef node);
    void remove_all_children();
    
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
    virtual void update() {}
    virtual void handle_input_event(const ZEvent &event) {}
    virtual bool should_draw(ZRenderContextRef context) { return true; }
    
    /* Renderable */
    void render(ZRenderContextRef context) override;
    
    /* Layout */
    virtual ZRect get_bounds() const override;
    virtual void set_bounds(const ZRect &bounds) override;
    
protected:
    virtual void _draw(ZRenderContextRef context);
    virtual void _update_internal();
    virtual void _handle_input_event_internal(const ZEvent &event);

private:
    void _remove_child_uid(unsigned uid);
    void _deorphan_child_node(ZNodeRef child);
    void _on_enter_internal();
    void _on_exit_internal();

    void _prepare_camera(ZRenderContextRef context);
    void _prepare_lights(ZRenderContextRef context);
    
    void _teardown_camera(ZRenderContextRef context);
    void _teardown_lights(ZRenderContextRef context);
    
protected:
    unsigned     _uid;
    ZVector      _position;
    ZMatrix      _transform;
    ZMatrix      _pos_transform;
    std::string  _name;
    ZGeometryRef _geometry;
    ZCameraRef   _camera;
    
    ZNode   *_parent; // weak
    ZScene  *_scene; // weak
    
    std::vector<ZNodeRef>   _children;
    std::vector<ZActionRef> _actions;
    
    std::vector<std::shared_ptr<ZLight>> _lights_used_for_draw;
    
    friend class ZScene;
};

ZGE_DEFINE_SREF_TYPE(ZNode);

ZGE_END_NAMESPACE
