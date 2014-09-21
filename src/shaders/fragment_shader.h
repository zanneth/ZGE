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

struct Material {
    vec4 color;
    sampler2D texture;
    int textureExists;
};

struct Light {
    vec3 position;
    vec4 color;
    int exists;
};

uniform Material material;
uniform Light ambientLight;
uniform Light diffuseLight;

out vec4 outputColor;

void main()
{
    vec4 pixel = vec4(1.0);
    
    if (material.color != vec4(0.0)) {
        pixel = material.color;
    }
    
    if (material.textureExists == 1) {
        vec4 texel = texture(material.texture, frag_texcoord0);
        pixel *= texel;
    }
    
    if (diffuseLight.exists == 1) {
        mat3 modelviewInv = transpose(inverse(mat3(modelview)));
        vec3 normal = normalize(modelviewInv * frag_normal);
        vec3 position = vec3(modelview * vec4(frag_position, 1.0));
        vec3 surfaceToLight = diffuseLight.position - position;
        
        float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
        brightness = clamp(brightness, 0.0, 1.0);
        
        vec4 ambient = vec4(0.0, 0.0, 0.0, 1.0);
        if (ambientLight.exists == 1) {
            ambient = vec4(ambientLight.color.rgb * ambientLight.color.a, 1.0);
        }
        
        vec4 diffuseColor = ambient + brightness * diffuseLight.color;
        pixel *= diffuseColor;
    }
    
    outputColor = pixel;
}

);

END_ZGE_NAMESPACE
