//
//  logger.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "logger.h"
#include <iostream>


namespace zge {

ZLogger *ZLogger::_instance = NULL;
ZLogger *LOGGER = ZLogger::Instance();

ZLogger* ZLogger::Instance()
{
    if (_instance == NULL)
        _instance = new ZLogger();
    return _instance;
}

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
    std::cerr << "ERROR (" << error.code << "): " << error.description << std::endl;
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

}
