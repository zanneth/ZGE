/*
 * camera.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#include <zge/camera.h>
#include <zge/logger.h>
#include <zge/scene.h>
#include <zge/viewport.h>

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

void ZCamera::set_transform(const ZAffine3 &transform)
{
    ZVec3 position = get_position();
    ZAffine3 translation = ZAffine3::Identity();
    translation.translate(position);
    
    ZAffine3 final_transform = translation * transform;
    final_transform.translate(-position);
    
    ZVec3 look = get_look_direction();
    look = final_transform * look;
    set_look_direction(look);
    
    ZNode::set_transform(transform);
}

void ZCamera::update(uint32_t dtime)
{
    ZVec3 velocity = get_velocity();
    
    if (velocity != ZVec3Zero) {
        ZVec3 position = get_position();
        ZVec3 look = get_look_direction();
        look += velocity;
        set_look_direction(look);
        
        ZAffine3 translation(ZAffine3::Identity());
        translation.translate(position);
        ZVec3 look_relative = translation * look;
        position += look_relative.normalized();
        set_position(position);
    }
}
    
#pragma mark - Private

void ZCamera::_construct_projection()
{
    if (_projection_dirty) {
        if (_scene) {
            ZViewport viewport = _scene->get_viewport();
            float aspect = std::max(viewport.width, viewport.height) / std::min(viewport.width, viewport.height);
            
            _projection_matrix = geometry::perspective(_field_of_view,
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
        _modelview_matrix = geometry::lookat(_position, _look_direction, ZVec3::UnitY());
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
