/*
 * fragment_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>
#include <zge/defines.h>

BEGIN_ZGE_NAMESPACE
    
const std::string ZFragmentShaderSource = "#version 150\n" + ZHEREDOC(

uniform vec4 materialColor;
out vec4 outputColor;

void main()
{
    outputColor = materialColor;
}

);

END_ZGE_NAMESPACE
