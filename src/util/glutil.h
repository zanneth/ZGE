//
//  glutil.h
//  ZGE
//
//  Created by Charles Magahern on 3/1/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#pragma once

#include <zge/opengl.h>
#include <zge/types.h>

BEGIN_ZGE_NAMESPACE

class ZGLUtil {
public:
    static GLenum gl_value_type_from_component_type(ZComponentType component_type);
    static GLenum gl_draw_mode_from_render_mode(ZRenderMode render_mode);
    static GLenum gl_target_from_buffer_target(ZBufferTarget target);
};

END_ZGE_NAMESPACE
