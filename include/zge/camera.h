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

class ZCamera : public ZNode {
    GLfloat _field_of_view;
    GLfloat _near_clip;
    GLfloat _far_clip;
    
    ZMat4 _projection_matrix;
    ZMat4 _modelview_matrix;
    ZVec3 _look_direction;
    
    bool _projection_dirty;
    bool _modelview_dirty;
    
public:
    ZCamera();
    
    /** Accessors **/
    GLfloat get_fov() { return _field_of_view; }
    void set_fov(GLfloat degrees) { _field_of_view = degrees; _projection_dirty = true; }
    GLfloat get_near_clipping_distance() { return _near_clip; }
    void set_near_clipping_distance(GLfloat distance) { _near_clip = distance; _projection_dirty = true; }
    GLfloat get_far_clipping_distance() { return _far_clip; }
    void set_far_clipping_distance(GLfloat distance) { _far_clip = distance; _projection_dirty = true; }
    
    const ZMat4* get_modelview_matrix() { return &_modelview_matrix; }
    const ZVec3* get_look_direction() { return &_look_direction; }
    void set_look_direction(const ZVec3 &look) { _look_direction = look; _modelview_dirty = true; }
    
    /** Open/Close **/
    void open();
    void close();
    
private:
    void _construct_projection();
    void _open_projection();
    void _close_projection();
    
    void _construct_modelview();
    void _open_modelview();
    void _close_modelview();
};

} // namespace zge
