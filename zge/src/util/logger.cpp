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
    
    printf("%s\r\n", buf);
}

void ZLogger::log(ZError error)
{
    std::cerr << "ERROR (" << error.code << "): " << error.description << std::endl;
}

void ZLogger::debugLog(const char *format, ...)
{
#if Z_DEBUG_LOGGING_ENABLED
    char buf[1024];
    
    va_list va;
    va_start(va, format);
    vsprintf(buf, format, va);
    va_end(va);
    
    // Copied everything to the buffer, may as well just call printf instead
    // of Log::log() when it'll be the same amount of code anyway.
    printf("%s\r\n", buf);
#endif
}

}
