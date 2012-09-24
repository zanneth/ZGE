/*
 * logger.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include <string>

namespace zge {

class logger : noncopyable {
public:
    static void log(const char *format, ...);
    static void log(const std::string str);
    static void warn(const char *format, ...);
};

} // namespace zge
