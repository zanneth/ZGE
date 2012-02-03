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
    static ZLogger *_instance;
    
public:
    static ZLogger* Instance();
    
    void log(const char *format, ...);
    void log(ZError error);
    void warn(const char *format, ...);

private:
    ZLogger() {}
    ZLogger(const ZLogger&) {}
    ~ZLogger() {}
};

extern ZLogger *LOGGER;

} // namespace zge