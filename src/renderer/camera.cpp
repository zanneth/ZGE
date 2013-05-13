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

void ZCamera::open()
{
    _open_projection();
    _open_modelview();
}

void ZCamera::close()
{
    _close_projection();
    _close_modelview();
}
    
#pragma mark - Node Overrides

void ZCamera::set_transform(const Affine3f &transform)
{
    Vector3f position = get_position();
    Affine3f translation = Affine3f::Identity();
    translation.translate(position);
    
    Affine3f final_transform = translation * transform;
    final_transform.translate(-position);
    
    Vector3f look = get_look_direction();
    look = final_transform * look;
    set_look_direction(look);
    
    ZNode::set_transform(transform);
}

#pragma mark - Private

void ZCamera::_construct_projection()
{
    if (_projection_dirty) {
        if (_scene) {
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
}

void ZCamera::_open_projection()
{
    if (_projection_dirty) {
        _construct_projection();
    }
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadMatrixf(_projection_matrix.data());
}

void ZCamera::_close_projection()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void ZCamera::_construct_modelview()
{
    if (_modelview_dirty) {
        _modelview_matrix = ZGeometry::lookat(_position, _look_direction, Vector3f::UnitY());
        _modelview_dirty = false;
    }
}

void ZCamera::_open_modelview()
{
    if (_modelview_dirty) {
        _construct_modelview();
    }
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(_modelview_matrix.data());
}

void ZCamera::_close_modelview()
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

} // namespace zge
