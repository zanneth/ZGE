/*
 * 3dcamera.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#include <zge/3dcamera.h>
#include <zge/engine.h>
#include <zge/node.h>
#include <zge/util.h>

#define DEFAULT_FOV         45.0f
#define DEFAULT_NEAR_CLIP   0.001f
#define DEFAULT_FAR_CLIP    10000.0f

ZGE_BEGIN_NAMESPACE

Z3DCamera::Z3DCamera() :
    _field_of_view(DEFAULT_FOV),
    _near_clip(DEFAULT_NEAR_CLIP),
    _far_clip(DEFAULT_FAR_CLIP),
    _projection_dirty(true),
    _modelview_dirty(true)
{}

#pragma mark - Camera Overrides

void Z3DCamera::open(ZRenderContextRef context)
{
    zassert(_current_context == nullptr, "Attempted to open a camera on a new context before closing with an existing context.");
    _current_context = context;
    
    _open_projection();
    _open_modelview();
    
    _open = true;
}

void Z3DCamera::close()
{
    _close_projection();
    _close_modelview();
    
    _current_context = nullptr;
    _open = false;
}

bool Z3DCamera::is_open() const
{
    return _open;
}

#pragma mark - Accessors

float Z3DCamera::get_fov() const { return _field_of_view; }
void Z3DCamera::set_fov(float degrees) { _field_of_view = degrees; _projection_dirty = true; }
float Z3DCamera::get_near_clipping_distance() const { return _near_clip; }
void Z3DCamera::set_near_clipping_distance(float distance) { _near_clip = distance; _projection_dirty = true; }
float Z3DCamera::get_far_clipping_distance() const { return _far_clip; }
void Z3DCamera::set_far_clipping_distance(float distance) { _far_clip = distance; _projection_dirty = true; }
ZVector Z3DCamera::get_look() const { return _look; }
void Z3DCamera::set_look(const ZVector &look) { _look = look; _modelview_dirty = true; }
ZVector Z3DCamera::get_position() const { return _position; }

#pragma mark - Node Overrides

void Z3DCamera::set_position(const ZVector &position)
{
    _position = position;
    _modelview_dirty = true;
}

void Z3DCamera::set_transform(const ZMatrix &transform)
{
    ZVector position = get_position();
    ZMatrix translation = ZMatrix::identity();
    translation.translate(position);
    
    ZMatrix final_transform = translation * transform;
    final_transform.translate(-position);
    
    ZVector look = get_look();
    look = final_transform * look;
    set_look(look);
}

#pragma mark - Private

void Z3DCamera::_construct_projection()
{
    if (_projection_dirty) {
        ZRect viewport_rect = ZEngine::instance()->get_viewport_rect();
        float viewport_width = viewport_rect.size.width;
        float viewport_height = viewport_rect.size.height;
        float aspect = viewport_width / viewport_height;
        
        _projection_matrix = ZMatrix::perspective(_field_of_view, aspect, _near_clip, _far_clip);
        _projection_dirty = false;
    }
}

void Z3DCamera::_open_projection()
{
    if (_projection_dirty) {
        _construct_projection();
    }
    
    _current_context->push_matrix(ZRENDER_MATRIX_PROJECTION, _projection_matrix);
}

void Z3DCamera::_close_projection()
{
    _current_context->pop_matrix(ZRENDER_MATRIX_PROJECTION);
}

void Z3DCamera::_construct_modelview()
{
    if (_modelview_dirty) {
        _modelview_matrix = ZMatrix::lookat(_position, _look, ZVector::unit_y());
        _modelview_dirty = false;
    }
}

void Z3DCamera::_open_modelview()
{
    if (_modelview_dirty) {
        _construct_modelview();
    }
    
    _current_context->push_matrix(ZRENDER_MATRIX_MODELVIEW, _modelview_matrix);
}

void Z3DCamera::_close_modelview()
{
    _current_context->pop_matrix(ZRENDER_MATRIX_MODELVIEW);
}

ZGE_END_NAMESPACE
