//
//  error.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/13/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/error.h"

namespace zge {

ZError::ZError() :
    _code(kUnknownError),
    _description("Unknown Error") {}

ZError::ZError(int code, string description) :
    _code(code),
    _description(description) {}

ZError ZError::NoError()
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

}
