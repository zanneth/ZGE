/*
 * fragment_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>

namespace zge {
    
const std::string ZFragmentShaderSource = "#version 150\n" + HEREDOC(

uniform vec4 ambientColor;

smooth in vec4 fragColor;
out vec4 outputColor;

void main()
{
    outputColor = fragColor * ambientColor;
}

);

} // namespace zge
