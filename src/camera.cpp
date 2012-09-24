/*
 * camera.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#include "zge/camera.h"
#include "zge/logger.h"
#include "zge/scene.h"
#include "zge/viewport.h"

#include <algorithm>

#define DEFAULT_FOV         45.0f
#define DEFAULT_NEAR_CLIP   0.001f
#define DEFAULT_FAR_CLIP    1000.0f

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


#pragma mark - Private

void ZCamera::_construct_projection()
{
    if (_projection_dirty) {
        if (_scene) {
            ZViewport viewport = _scene->get_viewport();
            float aspect = std::max(viewport.width, viewport.height) / std::min(viewport.width, viewport.height);
            
            _projection_matrix = ZMat4::perspective(_field_of_view,
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
    glLoadMatrixf(_projection_matrix.array);
}

void ZCamera::_close_projection()
{}

void ZCamera::_construct_modelview()
{
    if (_modelview_dirty) {
        _modelview_matrix = ZMat4::lookat(_position, _look_direction, ZVec3(0.0, 1.0, 0.0));
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
    glLoadMatrixf(_modelview_matrix.array);
}

void ZCamera::_close_modelview()
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

} // namespace zge
