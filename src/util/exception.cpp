/*
 * exception.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/24/2012
 */
 
#include <zge/exception.h>

#include <cstdio>
#include <sstream>

ZGE_BEGIN_NAMESPACE

ZException::ZException(int code_) :
    code(code_)
{
    switch (code_) {
        case ZUNKNOWN_EXCEPTION_CODE:
            description = "An unknown exception has occurred.";
            break;
        case ZNOT_IMPLEMENTED_EXCEPTION_CODE:
            description = "The functionality is not implemented.";
            break;
        case ZAPPLICATION_EXCEPTION_CODE:
            description = "The application created an exception.";
            break;
        case ZDISPLAY_EXCEPTION_CODE:
            description = "There was an exception in managing the display.";
            break;
        case ZENGINE_EXCEPTION_CODE:
            description = "General engine exception.";
            break;
        case ZMATHEMATIC_EXCEPTION_CODE:
            description = "There was a mathematical exception.";
            break;
        case ZFILE_EXCEPTION_CODE:
            description = "There was a filesystem exception.";
            break;
        case ZASSERTION_EXCEPTION_CODE:
            description = "Assertion failure.";
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

ZGE_END_NAMESPACE
