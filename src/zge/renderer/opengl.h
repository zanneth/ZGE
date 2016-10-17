/*
 * gl_includes.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/27/2012
 */

#pragma once

#if __has_include(<TargetConditionals.h>)
#include <TargetConditionals.h>
#endif

#ifdef __APPLE__
#if TARGET_OS_IPHONE
#   include <OpenGLES/ES3/gl.h>
#   include <OpenGLES/gltypes.h>
#else
#   include <OpenGL/gl3.h>
#   include <OpenGL/gltypes.h>
#endif
#else
#if OPENGL_ES
#   include <GLES2/gl2.h>
#   include <GLES2/gl2ext.h>
#   include <GLES2/gl2platform.h>
#if OPENGL_ES2
#   define glGenVertexArrays glGenVertexArraysOES
#   define glDeleteVertexArrays glDeleteVertexArraysOES
#   define glBindVertexArray glBindVertexArrayOES
#endif
#else
#   define GL_GLEXT_PROTOTYPES
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif
#endif
