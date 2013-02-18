/*
 * logger.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/noncopyable.h>
#include <string>
#include <sstream>

namespace zge {

class ZLogger : ZNoncopyable {
public:
    static void log(const char *format, ...);
    static void log(const std::string str);
    static void warn(const char *format, ...);
    
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
    
private:
    ZLogger();
    ~ZLogger();
};

} // namespace zge
