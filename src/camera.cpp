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
    _fieldOfView(DEFAULT_FOV),
    _nearClippingDistance(DEFAULT_NEAR_CLIP),
    _farClippingDistance(DEFAULT_FAR_CLIP),
    _projectionDirty(true),
    _modelViewDirty(true)
{}


#pragma mark - Open/Close

void ZCamera::open()
{
    _openProjection();
    _openModelView();
}

void ZCamera::close()
{
    _closeProjection();
    _closeModelView();
}


#pragma mark - Private

void ZCamera::_constructProjection()
{
    if (_projectionDirty) {
        if (_scene) {
            ZViewport viewport = _scene->getViewport();
            float aspect = std::max(viewport.width, viewport.height) / std::min(viewport.width, viewport.height);
            
            _projectionMatrix = ZMat4::perspective(_fieldOfView,
                                                      aspect,
                                                      _nearClippingDistance,
                                                      _farClippingDistance);
            _projectionDirty = false;
        }
    }
}

void ZCamera::_openProjection()
{
    if (_projectionDirty) {
        _constructProjection();
    }
    
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(_projectionMatrix.matrix);
}

void ZCamera::_closeProjection()
{}

void ZCamera::_constructModelView()
{
    if (_modelViewDirty) {
        _modelViewMatrix = ZMat4::lookat(_position, _lookDirection, ZVec3(0.0, 1.0, 0.0));
        _modelViewDirty = false;
    }
}

void ZCamera::_openModelView()
{
    if (_modelViewDirty) {
        _constructModelView();
    }
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(_modelViewMatrix.matrix);
}

void ZCamera::_closeModelView()
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

} // namespace zge
