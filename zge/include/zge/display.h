//
//  display.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/geometry.h"
#include "zge/error.h"
#include "zge/exception.h"

#include <string>

namespace zge {

using std::string;
using std::shared_ptr;

typedef shared_ptr<class ZDisplay> ZDisplayRef;

struct ZDisplayMode {
    bool windowed;
    int width;
    int height;
    float refreshRate;
    string windowTitle;
    
public:
    ZDisplayMode() :
        windowed(true),
        width(1024),
        height(768),
        refreshRate(1.0 / 60.0),
        windowTitle("Application") {}
};

class ZDisplayException : public ZException {
public:
    virtual const char* what() const throw()
    {
        return ("A display exception occurred: " + description).c_str();
    }
};

class ZDisplay {
protected:
    bool _isInitialized;
    ZDisplayMode _displayMode;
    ZCoordinateSystem<float> _coordinateSystem;
    
public:
    ZDisplay() = default;
    ZDisplay(const ZDisplayMode &displayMode);
    virtual ~ZDisplay() {}
    virtual void initialize() = 0;
    virtual void render(unsigned dtime) = 0;
    
    // Convenience method for setting width/height values in the current display mode
    void resize(int width, int height);
    
    /** Accessors **/
    bool isInitialized() { return _isInitialized; }
    
    ZDisplayMode getDisplayMode() const { return _displayMode; }
    virtual void setDisplayMode(const ZDisplayMode &mode);
    
    ZCoordinateSystem<float> getCoordinateSystem() const { return _coordinateSystem; }
    virtual void setCoordinateSystem(const ZCoordinateSystem<float> &coordSystem);
};

} // namespace zge