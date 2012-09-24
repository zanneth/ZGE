/*
 * exception.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */
 
#include "zge/exception.h"

#include <cstdio>
#include <sstream>

namespace zge {

exception::exception(int code_, std::string description_) :
    code(code_),
    description(description_)
{}

const char* exception::what() const throw()
{
    std::ostringstream oss;
    oss << "ZGE ERROR (" << code << "): " << description;
    if (extra_info.length() > 0) {
        oss << ' ' << extra_info;
    }
    
    return oss.str().c_str();
}

} // namespace zge
