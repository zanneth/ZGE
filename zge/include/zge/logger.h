//
//  logger.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

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