//
//  geometry.h
//  ZGE
//
//  Created by Charles Magahern on 1/13/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

namespace zge {

template <typename T>
struct ZVec {
public:
    T x, y, z;
    
public:
    ZVec() = default;
    ZVec(T x_, T y_, T z_) :
        x(x_),
        y(y_),
        z(z_) {}
    ZVec(T x_, T y_) :
        x(x_),
        y(y_),
        z(0) {}
    
    bool operator==(const ZVec &other)
    {
        return x == other.x
            && y == other.y
            && z == other.z;
    }
    
    bool operator!=(const ZVec &other) { return !operator==(other); }
};

typedef ZVec<float> ZVecf;
typedef ZVec<int> ZVeci;


template <typename T>
struct ZCoordinateSystem {
public:
    T width, height, depth;
    
public:
    ZCoordinateSystem() = default;
    ZCoordinateSystem(T width_, T height_, T depth_) :
        width(width_),
        height(height_),
        depth(depth_) {}
    
    bool isZero()
    {
        return width == 0 && height == 0 && depth == 0;
    }
    
    bool operator==(const ZCoordinateSystem &other)
    {
        return width == other.width 
            && height == other.height
            && depth == other.depth;
    }
    
    bool operator!=(const ZCoordinateSystem &other) { return !operator==(other); }
};

typedef ZCoordinateSystem<float> ZCoordinateSystemf;
typedef ZCoordinateSystem<int> ZCoordinateSystemi;

} // namespace zge