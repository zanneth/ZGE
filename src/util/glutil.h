//
//  glutil.h
//  ZGE
//
//  Created by Charles Magahern on 3/1/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#pragma once

#include <zge/defines.h>
#include <zge/opengl.h>
#include <zge/types.h>

ZGE_BEGIN_NAMESPACE

class ZGLUtil {
public:
    static GLenum gl_value_type_from_component_type(ZComponentType component_type);
    static GLenum gl_draw_mode_from_render_mode(ZRenderMode render_mode);
    static GLenum gl_target_from_buffer_target(ZBufferTarget target);
    static GLenum gl_usage_from_buffer_usage(ZBufferUsage usage);
    static size_t gl_host_size_for_component(ZComponentType component_type);
    static GLenum gl_format_from_pixel_format(ZPixelFormat format);
    static GLenum gl_shader_type_from_shader_type(ZShaderType type);
};

ZGE_END_NAMESPACE
