//
//  display.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_DISPLAY_H_
#define _ZGE_DISPLAY_H_

#include <string>
#include <zge/common/types.h>

namespace zge {
using std::string;

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

class ZDisplay {
protected:
    bool _isInitialized;
    ZDisplayMode _displayMode;
    ZCoordinateSystem _coordinateSystem;
    
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
    virtual ZError setDisplayMode(const ZDisplayMode &mode);
    
    ZCoordinateSystem getCoordinateSystem() const { return _coordinateSystem; }
    virtual ZError setCoordinateSystem(const ZCoordinateSystem &coordSystem);
};

}

#endif // _ZGE_DISPLAY_H_
