//
//  glutil.cpp
//  ZGE
//
//  Created by Charles Magahern on 3/1/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#include <zge/util/glutil.h>

ZGE_BEGIN_NAMESPACE

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
#if !OPENGL_ES
        case ZCOMPONENT_TYPE_DOUBLE:
            gltype = GL_DOUBLE;
            break;
#endif
        case ZCOMPONENT_TYPE_UNKNOWN:
        default:
            break;
    }
    return gltype;
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
        case ZBUFFER_TARGET_ELEMENT_ARRAY:
            gltype = GL_ELEMENT_ARRAY_BUFFER;
            break;
#if !OPENGL_ES2
        case ZBUFFER_TARGET_PIXEL_PACK:
            gltype = GL_PIXEL_PACK_BUFFER;
            break;
        case ZBUFFER_TARGET_PIXEL_UNPACK:
            gltype = GL_PIXEL_UNPACK_BUFFER;
            break;
        case ZBUFFER_TARGET_COPY_READ:
            gltype = GL_COPY_READ_BUFFER;
            break;
        case ZBUFFER_TARGET_COPY_WRITE:
            gltype = GL_COPY_WRITE_BUFFER;
            break;
        case ZBUFFER_TARGET_TRANSFORM_FEEDBACK:
            gltype = GL_TRANSFORM_FEEDBACK_BUFFER;
            break;
        case ZBUFFER_TARGET_UNIFORM:
            gltype = GL_UNIFORM_BUFFER;
            break;
#endif
#if !OPENGL_ES
        case ZBUFFER_TARGET_TEXTURE:
            gltype = GL_TEXTURE_BUFFER;
            break;
#endif
        default:
            break;
    }
    return gltype;
}

GLenum ZGLUtil::gl_usage_from_buffer_usage(ZBufferUsage usage)
{
    GLenum gltype = 0;
    
    ZBufferUsageFrequencyType frequency = usage.frequency;
    ZBufferUsageNature nature = usage.nature;
    switch (frequency) {
        case ZBUFFER_USAGE_FREQUENCY_DYNAMIC:
            switch (nature) {
                case ZBUFFER_USAGE_NATURE_DRAW:
                    gltype = GL_DYNAMIC_DRAW;
                    break;
#if !OPENGL_ES2
                case ZBUFFER_USAGE_NATURE_COPY:
                    gltype = GL_DYNAMIC_COPY;
                    break;
                case ZBUFFER_USAGE_NATURE_READ:
                    gltype = GL_DYNAMIC_READ;
                    break;
#endif
                default:
                    break;
            }
            break;
        case ZBUFFER_USAGE_FREQUENCY_STATIC:
            switch (nature) {
                case ZBUFFER_USAGE_NATURE_DRAW:
                    gltype = GL_STATIC_DRAW;
                    break;
#if !OPENGL_ES2
                case ZBUFFER_USAGE_NATURE_COPY:
                    gltype = GL_STATIC_COPY;
                    break;
                case ZBUFFER_USAGE_NATURE_READ:
                    gltype = GL_STATIC_READ;
                    break;
#endif
                default:
                    break;
            }
            break;
        case ZBUFFER_USAGE_FREQUENCY_STREAM:
            switch (nature) {
                case ZBUFFER_USAGE_NATURE_DRAW:
                    gltype = GL_STREAM_DRAW;
                    break;
#if !OPENGL_ES2
                case ZBUFFER_USAGE_NATURE_COPY:
                    gltype = GL_STREAM_COPY;
                    break;
                case ZBUFFER_USAGE_NATURE_READ:
                    gltype = GL_STREAM_READ;
                    break;
#endif
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
    return gltype;
}

size_t ZGLUtil::gl_host_size_for_component(ZComponentType component_type)
{
    size_t size = 0;
    switch (component_type) {
        case ZCOMPONENT_TYPE_BYTE:
            size = sizeof(GLbyte);
            break;
        case ZCOMPONENT_TYPE_UNSIGNED_BYTE:
            size = sizeof(GLubyte);
            break;
        case ZCOMPONENT_TYPE_SHORT:
            size = sizeof(GLshort);
            break;
        case ZCOMPONENT_TYPE_UNSIGNED_SHORT:
            size = sizeof(GLushort);
            break;
        case ZCOMPONENT_TYPE_INT:
            size = sizeof(GLint);
            break;
        case ZCOMPONENT_TYPE_UNSIGNED_INT:
            size = sizeof(GLuint);
            break;
        case ZCOMPONENT_TYPE_FLOAT:
            size = sizeof(GLfloat);
            break;
#if !OPENGL_ES
        case ZCOMPONENT_TYPE_DOUBLE:
            size = sizeof(GLdouble);
            break;
#endif
        case ZCOMPONENT_TYPE_UNKNOWN:
        default:
            break;
    }
    return size;
}

GLenum ZGLUtil::gl_format_from_pixel_format(ZPixelFormat format)
{
    GLenum gl_frmt = 0;
    switch (format) {
        case ZPIXEL_FORMAT_RGB:
            gl_frmt = GL_RGB;
            break;
        case ZPIXEL_FORMAT_RGBA:
            gl_frmt = GL_RGBA;
            break;
#if !OPENGL_ES2
        case ZPIXEL_FORMAT_R:
            gl_frmt = GL_RED;
            break;
        case ZPIXEL_FORMAT_RG:
            gl_frmt = GL_RG;
            break;
#endif
#if !OPENGL_ES
        case ZPIXEL_FORMAT_BGR:
            gl_frmt = GL_BGR;
            break;
        case ZPIXEL_FORMAT_BGRA:
            gl_frmt = GL_BGRA;
            break;
#endif
        default:
            break;
    }
    return gl_frmt;
}

GLenum ZGLUtil::gl_shader_type_from_shader_type(ZShaderType type)
{
    GLenum gltype = 0;
    switch (type) {
        case ZVERTEX_SHADER:
            gltype = GL_VERTEX_SHADER;
            break;
        case ZFRAGMENT_SHADER:
            gltype = GL_FRAGMENT_SHADER;
            break;
        default:
            break;
    }
    return gltype;
}

ZGE_END_NAMESPACE
