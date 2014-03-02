/*
 * fragment_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>

BEGIN_ZGE_NAMESPACE
    
const std::string ZFragmentShaderSource = "#version 150\n" + HEREDOC(

uniform vec4 materialColor;
out vec4 outputColor;

void main()
{
    outputColor = materialColor;
}

);

END_ZGE_NAMESPACE
