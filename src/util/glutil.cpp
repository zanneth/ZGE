//
//  glutil.cpp
//  ZGE
//
//  Created by Charles Magahern on 3/1/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#include <zge/glutil.h>

BEGIN_ZGE_NAMESPACE

GLenum ZGLUtil::gl_value_type_from_component_type(ZComponentType component_type)
{
    GLenum gltype = 0;
    switch (component_type) {
        case ZCOMPONENT_TYPE_BYTE:
            gltype = GL_BYTE;
            break;
        case ZCOMPONENT_TYPE_UNSIGNED_BYTE:
            gltype = GL_UNSIGNED_BYTE;
            break;
        case ZCOMPONENT_TYPE_SHORT:
            gltype = GL_SHORT;
            break;
        case ZCOMPONENT_TYPE_UNSIGNED_SHORT:
            gltype = GL_UNSIGNED_SHORT;
            break;
        case ZCOMPONENT_TYPE_INT:
            gltype = GL_INT;
            break;
        case ZCOMPONENT_TYPE_UNSIGNED_INT:
            gltype = GL_UNSIGNED_INT;
            break;
        case ZCOMPONENT_TYPE_FLOAT:
            gltype = GL_FLOAT;
            break;
        case ZCOMPONENT_TYPE_DOUBLE:
            gltype = GL_DOUBLE;
            break;
        case ZCOMPONENT_TYPE_UNKNOWN:
        default:
            break;
    }
    return 0;
}

GLenum ZGLUtil::gl_draw_mode_from_render_mode(ZRenderMode render_mode)
{
    GLenum gltype = 0;
    switch (render_mode) {
        case ZRENDER_MODE_POINTS:
            gltype = GL_POINTS;
            break;
        case ZRENDER_MODE_LINES:
            gltype = GL_LINES;
            break;
        case ZRENDER_MODE_LINE_LOOP:
            gltype = GL_LINE_LOOP;
            break;
        case ZRENDER_MODE_LINE_STRIP:
            gltype = GL_LINE_STRIP;
            break;
        case ZRENDER_MODE_TRIANGLES:
            gltype = GL_TRIANGLES;
            break;
        case ZRENDER_MODE_TRIANGLE_STRIP:
            gltype = GL_TRIANGLE_STRIP;
            break;
        case ZRENDER_MODE_TRIANGLE_FAN:
            gltype = GL_TRIANGLE_FAN;
            break;
        default:
            break;
    }
    return gltype;
}

GLenum ZGLUtil::gl_target_from_buffer_target(ZBufferTarget target)
{
    GLenum gltype = 0;
    switch (target) {
        case ZBUFFER_TARGET_ARRAY:
            gltype = GL_ARRAY_BUFFER;
            break;
        case ZBUFFER_TARGET_COPY_READ:
            gltype = GL_COPY_READ_BUFFER;
            break;
        case ZBUFFER_TARGET_COPY_WRITE:
            gltype = GL_COPY_WRITE_BUFFER;
            break;
        case ZBUFFER_TARGET_ELEMENT_ARRAY:
            gltype = GL_ELEMENT_ARRAY_BUFFER;
            break;
        case ZBUFFER_TARGET_PIXEL_PACK:
            gltype = GL_PIXEL_PACK_BUFFER;
            break;
        case ZBUFFER_TARGET_PIXEL_UNPACK:
            gltype = GL_PIXEL_UNPACK_BUFFER;
            break;
        case ZBUFFER_TARGET_TEXTURE:
            gltype = GL_TEXTURE_BUFFER;
            break;
        case ZBUFFER_TARGET_TRANSFORM_FEEDBACK:
            gltype = GL_TRANSFORM_FEEDBACK_BUFFER;
            break;
        case ZBUFFER_TARGET_UNIFORM:
            gltype = GL_UNIFORM_BUFFER;
            break;
        default:
            break;
    }
    return gltype;
}

END_ZGE_NAMESPACE
