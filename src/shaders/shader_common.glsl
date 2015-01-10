/*
 * shader_common.glsl
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/07/2015
 */

#pragma zge_version 150

#ifdef GL_ES

precision mediump float;

#define VSH_INPUT_ATTR attribute
#define FSH_INPUT_ATTR varying
#define OUTPUT varying
#define texture texture2D

#else

#define VSH_INPUT_ATTR in
#define FSH_INPUT_ATTR in
#define OUTPUT out

#endif
