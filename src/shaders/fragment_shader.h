/*
 * fragment_shader.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/07/2013
 */

#include <string>

const std::string ZFragmentShaderSource = HEREDOC(

void main()
{
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}

);
