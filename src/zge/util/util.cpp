/*
 * util.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */

#include <zge/util/util.h>
#include <zge/util/exception.h>
#include <chrono>
#include <cstdio>
#include <cmath>
#include <sstream>

ZGE_BEGIN_NAMESPACE

inline float ZUtil::degrees_to_radians(float degrees)
{
    return degrees * (M_PI / 180.0f);
}

std::string ZUtil::format(const char *format, ...)
{
    char *final_string = nullptr;
    unsigned size = 128;
    va_list args_list;
    bool string_formatted = false;
    
    while (!string_formatted) {
        if (final_string != nullptr) {
            delete[] final_string;
        }
        final_string = new char[size];
        
        va_start(args_list, format);
        int n = std::vsnprintf(final_string, size, format, args_list);
        va_end(args_list);
        
        if (n != -1 && n < size) {
            string_formatted = true;
        } else {
            size *= 2;
        }
    }
    
    std::string result(final_string);
    return result;
}

std::string ZUtil::join_components(const std::vector<std::string> &vec, std::string delimiter)
{
    std::ostringstream oss;
    unsigned idx = 0;
    size_t size = vec.size();
    for (const auto &cmp : vec) {
        oss << cmp;
        if (idx != size - 1) {
            oss << delimiter;
        }
        ++idx;
    }
    
    return oss.str();
}

void ZUtil::assert_true(bool expression, const char *format, ...) throw(ZException)
{
    if (!expression) {
        char error_message[512];
        va_list args_list;
        
        va_start(args_list, format);
        std::vsnprintf(error_message, 512, format, args_list);
        va_end(args_list);
        
        ZException exception(ZASSERTION_EXCEPTION_CODE);
        exception.extra_info = error_message;
        throw exception;
    }
}

ZTime ZUtil::get_current_time()
{
    return std::chrono::system_clock::now();
}

ZGE_END_NAMESPACE
