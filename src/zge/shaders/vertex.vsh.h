R"(

/*
 * vertex.vsh
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/07/2015
 */

#pragma zge_version 150

#ifdef GL_ES

precision highp float;

#define VSH_INPUT_ATTR attribute
#define FSH_INPUT_ATTR varying
#define OUTPUT varying
#define texture texture2D

#else

#define VSH_INPUT_ATTR in
#define FSH_INPUT_ATTR in
#define OUTPUT out

#endif

VSH_INPUT_ATTR vec4 position;
VSH_INPUT_ATTR vec3 normal;
VSH_INPUT_ATTR vec2 texcoord0;

uniform mat4 projection;
uniform mat4 modelview;

OUTPUT vec3 frag_position;
OUTPUT vec3 frag_normal;
OUTPUT vec2 frag_texcoord0;

void main()
{
    frag_position = vec3(position);
    frag_normal = normal;
    frag_texcoord0 = texcoord0;
    
    gl_Position = projection * modelview * position;
}

)"
