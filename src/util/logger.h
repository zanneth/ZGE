/*
 * logger.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/noncopyable.h>
#include <iostream>
#include <string>
#include <sstream>

namespace zge {

class ZLogger : ZNoncopyable {
public:
    static void log(const char *format, ...);
    static void log(const std::string str);
    static void log_error(const char *format, ...);
    static void log_error(const std::string str);
    
    template <typename T>
    static void log_array(T *array, unsigned count)
    {
        std::ostringstream stream;
        stream << "[";
        for (unsigned i = 0; i < count; ++i) {
            stream << array[i];
            if (i < count - 1) {
                stream << ", ";
            }
        }
        stream << "]";
        
        ZLogger::log(stream.str());
    }

protected:
    static void _logv(const char *format, va_list args, std::ostream &output_stream = std::cout);
    static void _logv(const std::string str, std::ostream &output_stream = std::cout);
    
private:
    ZLogger();
    ~ZLogger();
};

} // namespace zge

#define zlog(...) zge::ZLogger::log(__VA_ARGS__)
