/*
 * logger.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/logger.h>

ZGE_BEGIN_NAMESPACE

void ZLogger::log(const char *format, ...)
{
    va_list va;
    va_start(va, format);
    _logv(format, va);
    va_end(va);
}

void ZLogger::log(const std::string str)
{
    _logv(str);
}

void ZLogger::log_error(const char *format, ...)
{
    va_list va;
    va_start(va, format);
    _logv(format, va, std::cerr);
    va_end(va);
}

void ZLogger::log_error(const std::string str)
{
    _logv(str, std::cerr);
}

#pragma mark - Internal

void ZLogger::_logv(const char *format, va_list args, std::ostream &output_stream)
{
    char buf[1024];
    vsprintf(buf, format, args);
    output_stream << buf << std::endl;
}

void ZLogger::_logv(const std::string str, std::ostream &output_stream)
{
    output_stream << str << std::endl;
}

ZGE_END_NAMESPACE
