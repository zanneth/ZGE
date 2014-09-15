/*
 * fragment_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>
#include <zge/defines.h>

BEGIN_ZGE_NAMESPACE

const std::string ZFragmentShaderSource = "#version 150\n" + ZHEREDOC
(
                                                                      
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texcoord0;
 
uniform mat4 projection;
uniform mat4 modelview;
 
uniform vec4 materialColor;
uniform sampler2D materialTexture;
uniform int textureFlag;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform int lightFlag;
                                                                      
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
    
    vec4 diffuseColor = vec4(1.0);
    if (lightFlag == 1) {
        mat3 modelviewInv = transpose(inverse(mat3(modelview)));
        vec3 normal = normalize(modelviewInv * frag_normal);
        vec3 position = vec3(modelview * vec4(frag_position, 1.0));
        vec3 surfaceToLight = lightPosition - position;
        
        float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
        brightness = clamp(brightness, 0.0, 1.0);
        diffuseColor = brightness * lightColor;
    }
    
    outputColor = pixel * diffuseColor;
}

);

END_ZGE_NAMESPACE
