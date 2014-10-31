/*
 * orthocamera.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/camera.h>
#include <zge/defines.h>
#include <zge/types.h>
#include <memory>

ZGE_BEGIN_NAMESPACE

class ZOrthoCamera : public ZCamera {
    ZRect _clipping_rect;
    float _near_clip;
    float _far_clip;
    
    ZMatrix _projection;
    bool    _projection_dirty;
    bool    _open;
    
public:
    ZOrthoCamera();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZOrthoCamera);
    
    void open(ZRenderContextRef context) override;
    void close() override;
    bool is_open() const override;
    
    ZRect get_clipping_rect() const;
    void  set_clipping_rect(const ZRect &rect);
    
    float get_near_clip() const;
    void  set_near_clip(float near_clip);
    
    float get_far_clip() const;
    void  set_far_clip(float far_clip);
};

ZGE_DEFINE_SREF_TYPE(ZOrthoCamera);

ZGE_END_NAMESPACE
