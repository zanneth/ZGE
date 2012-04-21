/*
 * display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/geometry.h"
#include "zge/error.h"
#include "zge/exception.h"
#include "zge/noncopyable.h"

#include <string>

namespace zge {

struct ZDisplayMode {
    bool windowed;
    int width;
    int height;
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

class ZDisplayException : public ZException {
public:
    virtual const char* what() const throw()
    {
        return ("A display exception occurred: " + description).c_str();
    }
};

class ZDisplay : ZNonCopyable {
protected:
    bool _isInitialized;
    ZDisplayMode _displayMode;
    
public:
    ZDisplay() = default;
    ZDisplay(const ZDisplayMode &displayMode);
    virtual ~ZDisplay() {}
    
    /** Initialization **/
    virtual void initialize() = 0;
    
    
    /** Rendering **/
    virtual void render(unsigned dtime) = 0;
    
    
    // Convenience method for setting width/height values in the current display mode
    void resize(int width, int height);
    
    
    /** Accessors **/
    bool isInitialized() { return _isInitialized; }
    
    ZDisplayMode getDisplayMode() const { return _displayMode; }
    virtual void setDisplayMode(const ZDisplayMode &mode);
};

} // namespace zge
