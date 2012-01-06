//
//  logger.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_LOGGER_H_
#define _ZGE_LOGGER_H_

#include <zge/common/types.h>


namespace zge {

class ZLogger {
    static ZLogger *_instance;
    
public:
    static ZLogger* Instance();
    
    void log(const char *format, ...);
    void log(ZError error);
    void debugLog(const char *format, ...);

private:
    ZLogger() {}
    ZLogger(const ZLogger&) {}
    ~ZLogger() {}
};

extern ZLogger *LOGGER;

}

#endif // _ZGE_LOGGER_H_
