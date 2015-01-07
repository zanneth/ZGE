/*
 * gl_includes.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/27/2012
 */

#pragma once

#ifdef __APPLE__
#if TARGET_OS_IPHONE
#   include <OpenGLES/ES3/gl.h>
#   include <OpenGLES/gltypes.h>
#else
#   include <OpenGL/gl3.h>
#   include <OpenGL/gltypes.h>
#endif
#else
#   include <GL/gl3.h>
#endif
