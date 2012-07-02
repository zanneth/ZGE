/*
 * camera.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#pragma once

#include "zge/gl_includes.h"
#include "zge/node.h"
#include "zge/matrix.h"
#include "zge/vector.h"

namespace zge {

static const GLfloat kDefaultFieldOfView            = 45.0f;
static const GLfloat kDefaultNearClippingDistance   = 0.001f;
static const GLfloat kDefaultFarClippingDistance    = 1000.0f;

class ZCamera : public ZNode {
    GLfloat _fieldOfView;
    GLfloat _nearClippingDistance;
    GLfloat _farClippingDistance;
    
    ZMatrix4 _modelViewMatrix;
    ZVec3 _lookDirection;
    
public:
    ZCamera();
    
    /** Accessors **/
    GLfloat getFieldOfView() { return _fieldOfView; }
    void setFieldOfView(GLfloat degrees) { _fieldOfView = degrees; }
    GLfloat getNearClippingDistance() { return _nearClippingDistance; }
    void setNearClippingDistance(GLfloat distance) { _nearClippingDistance = distance; }
    GLfloat getFarClippingDistance() { return _farClippingDistance; }
    void setFarClippingDistance(GLfloat distance) { _farClippingDistance = distance; }
    
    const ZMatrix4* getModelViewMatrix() { return &_modelViewMatrix; }
    const ZVec3* getLookDirection() { return &_lookDirection; }
    void setLookDirection(const ZVec3 &look) { _lookDirection = look; }
};

} // namespace zge
