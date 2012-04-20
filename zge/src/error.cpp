/*
 * error.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/error.h"

namespace zge {

ZError::ZError() :
    _code(kUnknownError),
    _description("Unknown Error") {}

ZError::ZError(int code, std::string description) :
    _code(code),
    _description(description) {}

ZError ZError::noError()
{
    return ZError(kNoError, "No Error");
}


#pragma mark - Operators

bool ZError::operator==(const ZError &other)
{
    return _code == other._code
        && _description == other._description;
}

bool ZError::operator!=(const ZError &other)
{
    return !operator==(other);
}

} // namespace zge
