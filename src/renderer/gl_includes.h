/*
 * gl_includes.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/27/2012
 */
 
#pragma once

#ifdef __APPLE__
#if (Z_GLEW_ENABLED)
#   include <GL/glew.h>
#endif
#   include <OpenGL/OpenGL.h>
#	include <OpenGL/glu.h>
#	include <GLUT/glut.h>
#else
#if (Z_GLEW_ENABLED)
#   include <GL/glew.h>
#endif
#   include <GL/gl.h>
#	include <GL/glu.h>
#	include <GL/glut.h>
#endif
