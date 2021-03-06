/*
 * 3dcamera.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/renderer/camera.h>
#include <zge/core/defines.h>
#include <zge/math/matrix.h>
#include <zge/math/vector.h>
#include <memory>

ZGE_BEGIN_NAMESPACE

class Z3DCamera : public ZCamera {
public:
    Z3DCamera();
    
    ZGE_DEFINE_SREF_FUNCTIONS(Z3DCamera);
    
    void open(ZRenderContextRef context) override;
    bool is_open() const override;
    void close() override;
    
    ZRect   get_viewport_rect() const;
    void    set_viewport_rect(const ZRect &rect);
    
    float   get_fov() const;
    void    set_fov(float degrees);
    
    float   get_near_clipping_distance() const;
    void    set_near_clipping_distance(float distance);
    
    float   get_far_clipping_distance() const;
    void    set_far_clipping_distance(float distance);
    
    ZVector get_look() const;
    void    set_look(const ZVector &look);
    
    ZVector get_position() const;
    void    set_position(const ZVector &position);
    
    // convenience for setting above properties
    void    set_transform(const ZMatrix &transform);
    
private:
    void _construct_projection();
    void _open_projection();
    void _close_projection();
    
    void _construct_modelview();
    void _open_modelview();
    void _close_modelview();
    
protected:
    float _field_of_view;
    float _near_clip;
    float _far_clip;
    
    ZMatrix _projection_matrix;
    ZMatrix _modelview_matrix;
    ZVector _look;
    ZVector _position;
    ZRect   _viewport;
    
    bool _open;
    bool _projection_dirty;
    bool _modelview_dirty;
};

ZGE_DEFINE_SREF_TYPE(Z3DCamera);

ZGE_END_NAMESPACE
