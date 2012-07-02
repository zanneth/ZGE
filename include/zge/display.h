/*
 * display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include <tuple>
#include <string>

namespace zge {

static const std::tuple<unsigned, unsigned> kDefaultDisplaySize(1024, 768);
static const float kDefaultDisplayRefreshRate   = 1.0f / 60.0f;
static const char *kDefaultWindowTitle          = "Application";

struct ZDisplayMode {
    bool windowed;
    unsigned width;
    unsigned height;
    float refreshRate;
    std::string windowTitle;
    
public:
    ZDisplayMode() :
        windowed(true),
        width(std::get<0>(kDefaultDisplaySize)),
        height(std::get<1>(kDefaultDisplaySize)),
        refreshRate(kDefaultDisplayRefreshRate),
        windowTitle(kDefaultWindowTitle) {}
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
