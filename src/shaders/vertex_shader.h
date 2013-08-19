/*
 * vertex_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>

namespace zge {
    
const std::string ZVertexShaderSource = "#version 150\n" + HEREDOC(

in vec4 position;
in vec4 color;

uniform mat4 projection;
uniform mat4 modelview;

smooth out vec4 fragColor;

void main()
{
    fragColor = color;
    gl_Position = projection * modelview * position;
}

);

} // namespace zge
