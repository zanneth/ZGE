/*
 * 3dcamera.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/camera.h>
#include <zge/defines.h>
#include <zge/matrix.h>
#include <zge/vector.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

class Z3DCamera : public ZCamera {
public:
    Z3DCamera();
    
    void open(ZRenderContextRef context) override;
    bool is_open() const override;
    void close() override;
    
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
    
    bool _open;
    bool _projection_dirty;
    bool _modelview_dirty;
};

typedef std::shared_ptr<Z3DCamera> Z3DCameraRef;

END_ZGE_NAMESPACE
