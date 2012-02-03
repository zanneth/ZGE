//
//  logger.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/logger.h"
#include <iostream>

namespace zge {

void ZLogger::log(const char *format, ...)
{
    char buf[1024];
    
    va_list va;
    va_start(va, format);
    vsprintf(buf, format, va);
    va_end(va);
    
    std::cout << buf << std::endl;
}

void ZLogger::log(ZError error)
{
    std::cerr << "ERROR (" << error.getCode() << "): " << error.getDescription() << std::endl;
}

void ZLogger::warn(const char *format, ...)
{
    char buf[1024];
    
    va_list va;
    va_start(va, format);
    vsprintf(buf, format, va);
    va_end(va);
    
    std::cout << "WARNING: " << buf << std::endl;
}

} // namespace zge