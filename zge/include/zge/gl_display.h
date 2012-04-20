/*
 * gl_display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/display.h"
#include "zge/noncopyable.h"

#include <SDL/SDL.h>
#include <string>

namespace zge {

class ZGLDisplay : public ZDisplay, private ZNonCopyable {
    SDL_Surface *_surface;
    unsigned _lastRender;
    
public:
    ZGLDisplay();
    ZGLDisplay(const ZDisplayMode &mode);
    ~ZGLDisplay();
    
    /** Overrides **/
    void initialize() override;
    void render(unsigned dtime) override;
    
    void setDisplayMode(const ZDisplayMode &mode) override;
    void setCoordinateSystem(const ZCoordinateSystemf &coordSystem) override;
    
private:
    void _loadSurface();
    void _loadViewport();
    void _loadCoordinateSystem();
    
    void _initOpenGL();
    
    void _changeWindowTitle(std::string newTitle);
};

} // namespace zge
