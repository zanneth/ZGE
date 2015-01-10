/*
 * fragment.fsh
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/07/2015
 */

#pragma zge_include "shader_common.glsl"

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

FSH_INPUT_ATTR vec3 frag_position;
FSH_INPUT_ATTR vec3 frag_normal;
FSH_INPUT_ATTR vec2 frag_texcoord0;

uniform mat4 projection;
uniform mat4 modelview;

uniform Material material;
uniform Light ambientLight;
uniform Light diffuseLight;

#ifndef GL_ES
OUTPUT vec4 outputColor;
#endif

mat3 zge_transpose(mat3 m)
{
    return mat3(m[0][0], m[1][0], m[2][0],
                m[0][1], m[1][1], m[2][1],
                m[0][2], m[1][2], m[2][2]);
}

mat3 zge_inverse(mat3 m)
{
    float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2];
    float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2];
    float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2];
    
    float b01 = a22 * a11 - a12 * a21;
    float b11 = -a22 * a10 + a12 * a20;
    float b21 = a21 * a10 - a11 * a20;
    
    float det = a00 * b01 + a01 * b11 + a02 * b21;
    
    return mat3(b01, (-a22 * a01 + a02 * a21), (a12 * a01 - a02 * a11),
                b11, (a22 * a00 - a02 * a20), (-a12 * a00 + a02 * a10),
                b21, (-a21 * a00 + a01 * a20), (a11 * a00 - a01 * a10)) / det;
}

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
        mat3 modelviewInv = zge_transpose(zge_inverse(mat3(modelview)));
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
    
#ifndef GL_ES
    outputColor = pixel;
#else
    gl_FragColor = pixel;
#endif
}
