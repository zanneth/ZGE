/*
 * logger.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
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

void ZLogger::log(const std::string str)
{
    std::cout << str << std::endl;
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
