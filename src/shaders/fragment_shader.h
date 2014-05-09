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
                                                                      
in vec2 frag_texcoord0;
                                                                      
uniform vec4 materialColor;
uniform sampler2D materialTexture;
out vec4 outputColor;

void main()
{
    vec4 texcolor = texture(materialTexture, frag_texcoord0);
    outputColor = texcolor * materialColor;
}

);

END_ZGE_NAMESPACE
