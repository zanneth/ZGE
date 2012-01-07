//
//  types.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_TYPES_H_
#define _ZGE_TYPES_H_

#include <string>

#define ZGE_UNKNOWN_ERROR       -1
#define ZGE_SDL_ERROR           1
#define ZGE_DISPLAY_INIT_ERROR  2


namespace zge {

struct ZError {
    int code;
    std::string description;
    
    ZError() :
        code(ZGE_UNKNOWN_ERROR),
        description("Unknown Error") {}
    
    ZError(int code_, std::string description_) :
        code(code_),
        description(description_) {}
    
    static ZError ZErrorNone()
    {
        return ZError(0, "No Error");
    }
};

struct ZCoordinateSystem {
    float width;
    float height;
    float depth;
    
    ZCoordinateSystem() : 
        width(0.0),
        height(0.0),
        depth(0.0) {}
    
    ZCoordinateSystem(float width_, float height_, float depth_) :
        width(width_),
        height(height_),
        depth(depth_) {}
    
    bool operator==(const ZCoordinateSystem &other)
    {
        return width == other.width
                && height == other.height
                && depth == other.depth;
    }
    
    bool operator!=(const ZCoordinateSystem &other) { return !operator==(other); }
};
static const ZCoordinateSystem ZCoordinateSystemZero = ZCoordinateSystem(0.0, 0.0, 0.0);

}

#endif // _ZGE_TYPES_H_
