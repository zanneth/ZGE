/*
 * orthocamera.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#include <zge/orthocamera.h>

ZGE_BEGIN_NAMESPACE

ZOrthoCamera::ZOrthoCamera() :
    _clipping_rect({{-1.0, -1.0}, {2.0, 2.0}}),
    _near_clip(0.0),
    _far_clip(1.0),
    _projection_dirty(true)
{}

#pragma mark - Camera Overrides

void ZOrthoCamera::open(ZRenderContextRef context)
{
    _current_context = context;
    
    if (_projection_dirty) {
        float left = _clipping_rect.origin.x;
        float right = _clipping_rect.origin.x + _clipping_rect.size.width;
        float top = _clipping_rect.origin.y;
        float bottom = _clipping_rect.origin.y + _clipping_rect.size.height;
        
        _projection = ZMatrix::ortho(left, right, bottom, top, _near_clip, _far_clip);
        _projection_dirty = false;
    }
    
    _current_context->push_matrix(ZRENDER_MATRIX_PROJECTION, _projection);
    _current_context->push_matrix(ZRENDER_MATRIX_MODELVIEW, ZMatrix::identity());
    _open = true;
}

void ZOrthoCamera::close()
{
    _current_context->pop_matrix(ZRENDER_MATRIX_PROJECTION);
    _current_context->pop_matrix(ZRENDER_MATRIX_MODELVIEW);
    _current_context = nullptr;
    _open = false;
}

bool ZOrthoCamera::is_open() const
{
    return _open;
}

#pragma mark - Accessors

ZRect ZOrthoCamera::get_clipping_rect() const { return _clipping_rect; }
void ZOrthoCamera::set_clipping_rect(const ZRect &rect) { _clipping_rect = rect; }
float ZOrthoCamera::get_near_clip() const { return _near_clip; }
void ZOrthoCamera::set_near_clip(float near_clip) { _near_clip = near_clip; }
float ZOrthoCamera::get_far_clip() const { return _far_clip; }
void ZOrthoCamera::set_far_clip(float far_clip) { _far_clip = far_clip; }

ZGE_END_NAMESPACE
