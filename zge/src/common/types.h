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
#define ZGE_NO_ERROR            0
#define ZGE_APPLICATION_ERROR   1
#define ZGE_SDL_ERROR           2
#define ZGE_DISPLAY_INIT_ERROR  3

namespace zge {
using std::string;

struct ZError {
    int code;
    string description;
    
public:
    ZError() :
        code(ZGE_UNKNOWN_ERROR),
        description("Unknown Error") {}
    
    ZError(int code_, std::string description_) :
        code(code_),
        description(description_) {}
    
    static ZError ZErrorNone()
    {
        return ZError(ZGE_NO_ERROR, "No Error");
    }
    
    bool operator==(const ZError &other)
    {
        return code == other.code && description == other.description;
    }
    
    bool operator!=(const ZError &other) { return !operator==(other); }
};

struct ZCoordinateSystem {
    float width;
    float height;
    float depth;

public:
    ZCoordinateSystem() = default;
    
    ZCoordinateSystem(float width_, float height_, float depth_) :
        width(width_),
        height(height_),
        depth(depth_) {}
    
    bool isZero()
    {
        return width == 0.0 && height == 0.0 && depth == 0.0;
    }
    
    bool operator==(const ZCoordinateSystem &other)
    {
        return width == other.width
                && height == other.height
                && depth == other.depth;
    }
    
    bool operator!=(const ZCoordinateSystem &other) { return !operator==(other); }
};

struct ZVertex {
    float x;
    float y;
    float z;
    
    
};

}

#endif // _ZGE_TYPES_H_
