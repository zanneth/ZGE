/*
 * display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include <string>

namespace zge {

struct ZDisplayMode {
    bool windowed;
    unsigned width;
    unsigned height;
    float refreshRate;
    std::string windowTitle;
    
public:
    ZDisplayMode() :
        windowed(true),
        width(1024),
        height(768),
        refreshRate(1.0 / 60.0),
        windowTitle("Application") {}
};

class ZDisplay : ZNonCopyable {
protected:
    bool _isInitialized;
    ZDisplayMode _displayMode;

protected: // Only a display manager can create displays
    ZDisplay() = default;
    ZDisplay(const ZDisplayMode &displayMode);
    
public:
    virtual ~ZDisplay() {}
    
    /** Initialization **/
    virtual void initialize() = 0;
    
    /** Rendering **/
    virtual void render(unsigned dtime) = 0;
    
    // Convenience method for setting width/height values in the current display mode
    void resize(int width, int height);
    
    /** Accessors **/
    bool isInitialized() { return _isInitialized; }
    
    ZDisplayMode getDisplayMode() { return _displayMode; }
    virtual void setDisplayMode(const ZDisplayMode &mode);
    
    /** Friends **/
    friend class ZDisplayManager;
};

} // namespace zge
