/*
 * logger.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/error.h"

namespace zge {

class ZLogger {
public:
    static void log(const char *format, ...);
    static void log(ZError error);
    static void warn(const char *format, ...);
};

} // namespace zge
