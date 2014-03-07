/*
 * camera.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/matrix.h>
#include <zge/node.h>
#include <zge/noncopyable.h>
#include <zge/render_context.h>
#include <zge/vector.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZCamera> ZCameraRef;

class ZCamera : public ZNode {
    float _field_of_view;
    float _near_clip;
    float _far_clip;
    
    ZMatrix _projection_matrix;
    ZMatrix _modelview_matrix;
    ZVector _look;
    
    ZRenderContextRef _current_context;
    
    bool _open;
    bool _projection_dirty;
    bool _modelview_dirty;
    
public:
    ZCamera();
    
    /* Accessors */
    float get_fov() { return _field_of_view; }
    void set_fov(float degrees) { _field_of_view = degrees; _projection_dirty = true; }
    float get_near_clipping_distance() { return _near_clip; }
    void set_near_clipping_distance(float distance) { _near_clip = distance; _projection_dirty = true; }
    float get_far_clipping_distance() { return _far_clip; }
    void set_far_clipping_distance(float distance) { _far_clip = distance; _projection_dirty = true; }
    
    ZVector get_look() { return _look; }
    void set_look(const ZVector &look) { _look = look; _modelview_dirty = true; }
    
    ZMatrix get_modelview_matrix() { return _modelview_matrix; }
    
    /* Open/Close */
    void open(ZRenderContextRef context);
    bool is_open() const { return _open; }
    void close();
    
    /* Node Overrides */
    void set_position(const ZVector &position) override;
    void set_transform(const ZMatrix &transform) override;
    
private:
    void _construct_projection();
    void _open_projection();
    void _close_projection();
    
    void _construct_modelview();
    void _open_modelview();
    void _close_modelview();
};

END_ZGE_NAMESPACE
