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

namespace zge {

ZCamera::ZCamera() :
    _fieldOfView(kDefaultFieldOfView),
    _nearClippingDistance(kDefaultNearClippingDistance),
    _farClippingDistance(kDefaultFarClippingDistance),
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
        ZViewport viewport = _scene->getViewport();
        float aspect = std::max(viewport.width, viewport.height) / std::min(viewport.width, viewport.height);
        
        _projectionMatrix = ZMatrix4::perspective(_fieldOfView,
                                                  aspect,
                                                  _nearClippingDistance,
                                                  _farClippingDistance);
        _projectionDirty = false;
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
        _modelViewMatrix = ZMatrix4::lookAt(_position, _lookDirection, ZVec3(0.0, 1.0, 0.0));
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
