//
//  util.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "util.h"
#include <iostream>

namespace zge {
namespace util {

#pragma mark - Fatal Errors

void fatalError()
{
    exit(ZGE_UNKNOWN_ERROR);
}

void fatalError(ZError error)
{
    std::cerr << "FATAL ERROR(" << error.code << "): " << error.description << std::endl;
    if (error.code != 0) {
        exit(error.code);
    } else {
        exit(ZGE_UNKNOWN_ERROR);
    }
}

}
}
