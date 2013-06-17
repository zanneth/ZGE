/*
 * vertex_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>

namespace zge {
    
const std::string ZVertexShaderSource = HEREDOC(

uniform mat4 projection;
uniform mat4 modelview;
attribute vec4 position;

void main()
{
    gl_Position = projection * modelview * position;
}

);

} // namespace zge
