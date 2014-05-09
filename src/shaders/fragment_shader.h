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
uniform int textureFlag;
                                                                      
out vec4 outputColor;

void main()
{
    vec4 pixel = vec4(1.0);
    
    if (materialColor != vec4(0.0)) {
        pixel = materialColor;
    }
    
    if (textureFlag == 1) {
        vec4 texel = texture(materialTexture, frag_texcoord0);
        pixel *= texel;
    }
    
    outputColor = pixel;
}

);

END_ZGE_NAMESPACE
