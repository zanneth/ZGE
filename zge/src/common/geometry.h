//
//  geometry.h
//  ZGE
//
//  Created by Charles Magahern on 1/13/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_GEOMETRY_H_
#define _ZGE_GEOMETRY_H_

namespace zge {

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


struct ZPoint {
    float x;
    float y;
    float z;
    
public:
    ZPoint() = default;
    ZPoint(float x_, float y_, float z_) :
        x(x_),
        y(y_),
        z(z_) {}
    ZPoint(float x_, float y_) :
        x(x_),
        y(y_),
        z(0.0) {}
    
    bool operator==(const ZPoint &other)
    {
        return x == other.x
            && y == other.y
            && z == other.z;
    }
    
    bool operator!=(const ZPoint &other) { return !operator==(other); }
};

}

#endif // _ZGE_GEOMETRY_H_
