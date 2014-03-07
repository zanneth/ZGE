/*
 * vertex_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>
#include <zge/defines.h>

BEGIN_ZGE_NAMESPACE
    
const std::string ZVertexShaderSource = "#version 150\n" + ZHEREDOC(

in vec4 position;

uniform mat4 projection;
uniform mat4 modelview;

void main()
{
    gl_Position = projection * modelview * position;
}

);

END_ZGE_NAMESPACE
