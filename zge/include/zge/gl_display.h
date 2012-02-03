//
//  gl_display.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/display.h"

#include <SDL/SDL.h>
#include <string>

namespace zge {
using std::string;

class ZGLDisplay : public ZDisplay {
    SDL_Surface *_surface;
    unsigned _lastRender;
    
public:
    ZGLDisplay();
    ZGLDisplay(const ZDisplayMode &mode);
    ~ZGLDisplay();
    
    /** Overrides **/
    void initialize() override;
    void render(unsigned dtime) override;
    
    ZError setDisplayMode(const ZDisplayMode &mode) override;
    ZError setCoordinateSystem(const ZCoordinateSystem &coordSystem) override;
    
private:
    void _loadSurface();
    void _loadViewport();
    void _loadCoordinateSystem();
    
    void _initOpenGL();
    
    void _changeWindowTitle(string newTitle);
};

} // namespace zge