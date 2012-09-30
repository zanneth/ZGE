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

ZException::ZException(int code_) :
    code(code_)
{
    switch (code_) {
        case UNKNOWN_EXCEPTION_CODE:
            description = "An unknown exception has occurred.";
            break;
        case NOT_IMPLEMENTED_EXCEPTION_CODE:
            description = "The functionality is not implemented.";
            break;
        case APPLICATION_EXCEPTION_CODE:
            description = "The application created an exception.";
            break;
        case DISPLAY_EXCEPTION_CODE:
            description = "There was an exception in managing the display.";
            break;
        case ENGINE_EXCEPTION_CODE:
            description = "General engine exception.";
            break;
        case MATHEMATIC_EXCEPTION_CODE:
            description = "There was a mathematical exception.";
            break;
        case FILE_EXCEPTION_CODE:
            description = "There was a filesystem exception.";
            break;
        default:
            break;
    }
}

const char* ZException::what() const throw()
{
    std::ostringstream oss;
    oss << "ZGE ERROR (" << code << "): " << description;
    if (extra_info.length() > 0) {
        oss << ' ' << extra_info;
    }
    
    return oss.str().c_str();
}

bool ZException::operator==(const ZException &other)
{
    return code == other.code;
}

bool ZException::operator!=(const ZException &other)
{
    return !operator==(other);
}

} // namespace zge
