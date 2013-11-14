/*
 * camera.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#include <zge/camera.h>
#include <zge/engine.h>
#include <zge/logger.h>
#include <zge/scene.h>
#include <zge/util.h>

#include <algorithm>

#define DEFAULT_FOV         45.0f
#define DEFAULT_NEAR_CLIP   0.001f
#define DEFAULT_FAR_CLIP    10000.0f

namespace zge {

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
}

void ZCamera::close()
{
    _close_projection();
    _close_modelview();
    
    _current_context = nullptr;
}
    
#pragma mark - Node Overrides

void ZCamera::set_position(const Vector3f &position)
{
    ZNode::set_position(position);
    _modelview_dirty = true;
}

void ZCamera::set_transform(const Affine3f &transform)
{
    Vector3f position = get_position();
    Affine3f translation = Affine3f::Identity();
    translation.translate(position);
    
    Affine3f final_transform = translation * transform;
    final_transform.translate(-position);
    
    Vector3f look = get_look();
    look = final_transform * look;
    set_look(look);
    
    ZNode::set_transform(transform);
}

#pragma mark - Private

void ZCamera::_construct_projection()
{
    if (_projection_dirty) {
        AlignedBox2f viewport_rect = ZEngine::instance()->get_viewport_rect();
        float viewport_width = viewport_rect.max().x();
        float viewport_height = viewport_rect.max().y();
        float aspect = std::max(viewport_width, viewport_height) / std::min(viewport_width, viewport_height);
        
        _projection_matrix = ZGeometry::perspective(_field_of_view,
                                                   aspect,
                                                   _near_clip,
                                                   _far_clip);
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
        _modelview_matrix = ZGeometry::lookat(_position, _look, Vector3f::UnitY());
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

} // namespace zge
