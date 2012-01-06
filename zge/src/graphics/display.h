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

struct ZDisplayMode {
    bool windowed;
    int width;
    int height;
    float refreshRate;
    std::string windowTitle;
};

class ZDisplay {
protected:
    bool _isInitialized;
    ZDisplayMode _displayMode;
    ZCoordinateSystem _coordinateSystem;
    
public:
    ZDisplay();
    virtual ~ZDisplay() {}
    virtual void initialize() = 0;
    virtual void render() = 0;
    
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
