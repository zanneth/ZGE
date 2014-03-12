/*
 * camera.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#include <zge/camera.h>
#include <zge/engine.h>
#include <zge/logger.h>
#include <zge/opengl.h>
#include <zge/scene.h>
#include <zge/util.h>

#include <algorithm>

#define DEFAULT_FOV         45.0f
#define DEFAULT_NEAR_CLIP   0.001f
#define DEFAULT_FAR_CLIP    10000.0f

BEGIN_ZGE_NAMESPACE

ZCamera::ZCamera() :
    _field_of_view(DEFAULT_FOV),
    _near_clip(DEFAULT_NEAR_CLIP),
    _far_clip(DEFAULT_FAR_CLIP),
    _projection_dirty(true),
    _modelview_dirty(true)
{}

#pragma mark - Open/Close

void ZCamera::open(ZRenderContextRef context)
{
    zassert(_current_context == nullptr, "Attempted to open a camera on a new context before closing with an existing context.");
    _current_context = context;
    
    _open_projection();
    _open_modelview();
    
    _open = true;
}

void ZCamera::close()
{
    _close_projection();
    _close_modelview();
    
    _current_context = nullptr;
    _open = false;
}
    
#pragma mark - Node Overrides

void ZCamera::set_position(const ZVector &position)
{
    _position = position;
    _modelview_dirty = true;
}

void ZCamera::set_transform(const ZMatrix &transform)
{
    ZNode::set_transform(transform);
    
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

void ZCamera::_construct_projection()
{
    if (_projection_dirty) {
        ZRect viewport_rect = ZEngine::instance()->get_viewport_rect();
        float viewport_width = viewport_rect.size.width;
        float viewport_height = viewport_rect.size.height;
        float aspect = std::max(viewport_width, viewport_height) / std::min(viewport_width, viewport_height);
        
        _projection_matrix = ZMatrix::perspective(_field_of_view, aspect, _near_clip, _far_clip);
        _projection_dirty = false;
    }
}

void ZCamera::_open_projection()
{
    if (_projection_dirty) {
        _construct_projection();
    }
    
    _current_context->push_matrix(ZRENDER_MATRIX_PROJECTION, _projection_matrix);
}

void ZCamera::_close_projection()
{
    _current_context->pop_matrix(ZRENDER_MATRIX_PROJECTION);
}

void ZCamera::_construct_modelview()
{
    if (_modelview_dirty) {
        _modelview_matrix = ZMatrix::lookat(_position, _look, ZVector::unit_y());
        _modelview_dirty = false;
    }
}

void ZCamera::_open_modelview()
{
    if (_modelview_dirty) {
        _construct_modelview();
    }
    
    _current_context->push_matrix(ZRENDER_MATRIX_MODELVIEW, _modelview_matrix);
}

void ZCamera::_close_modelview()
{
    _current_context->pop_matrix(ZRENDER_MATRIX_MODELVIEW);
}

END_ZGE_NAMESPACE
