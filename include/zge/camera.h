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

#include <memory>

namespace zge {

typedef std::shared_ptr<class ZCamera> ZCameraRef;

static const GLfloat kDefaultFieldOfView            = 45.0f;
static const GLfloat kDefaultNearClippingDistance   = 0.001f;
static const GLfloat kDefaultFarClippingDistance    = 1000.0f;

class ZCamera : public ZNode {
    GLfloat _fieldOfView;
    GLfloat _nearClippingDistance;
    GLfloat _farClippingDistance;
    
    ZMatrix4 _projectionMatrix;
    ZMatrix4 _modelViewMatrix;
    ZVec3 _lookDirection;
    
    bool _projectionDirty;
    bool _modelViewDirty;
    
public:
    ZCamera();
    
    /** Accessors **/
    GLfloat getFieldOfView() { return _fieldOfView; }
    void setFieldOfView(GLfloat degrees) { _fieldOfView = degrees; _projectionDirty = true; }
    GLfloat getNearClippingDistance() { return _nearClippingDistance; }
    void setNearClippingDistance(GLfloat distance) { _nearClippingDistance = distance; _projectionDirty = true; }
    GLfloat getFarClippingDistance() { return _farClippingDistance; }
    void setFarClippingDistance(GLfloat distance) { _farClippingDistance = distance; _projectionDirty = true; }
    
    const ZMatrix4* getModelViewMatrix() { return &_modelViewMatrix; }
    const ZVec3* getLookDirection() { return &_lookDirection; }
    void setLookDirection(const ZVec3 &look) { _lookDirection = look; _modelViewDirty = true; }
    
    /** Open/Close **/
    void open();
    void close();
    
private:
    void _constructProjection();
    void _openProjection();
    void _closeProjection();
    
    void _constructModelView();
    void _openModelView();
    void _closeModelView();
};

} // namespace zge
