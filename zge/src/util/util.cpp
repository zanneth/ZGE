//
//  util.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/util.h"
#include <iostream>

namespace zge {
namespace util {

#pragma mark - Fatal Errors

void fatalError()
{
    exit(kUnknownError);
}

void fatalError(ZError error)
{
    int errorCode = error.getCode();
    std::string errorDescription = error.getDescription();
    
    std::cerr << "FATAL ERROR(" << errorCode << "): " << errorDescription << std::endl;
    if (errorCode != 0) {
        exit(errorCode);
    } else {
        exit(kUnknownError);
    }
}

}
}
