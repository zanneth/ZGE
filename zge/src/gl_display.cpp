//
//  gl_display.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "zge/gl_display.h"
#include "zge/logger.h"
#include "zge/util.h"

#include <iostream>
#include <string>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

namespace zge {

ZGLDisplay::ZGLDisplay() : ZDisplay(),
    _surface(nullptr) {}

ZGLDisplay::ZGLDisplay(const ZDisplayMode &mode) : ZDisplay(mode),
    _surface(nullptr) {}

ZGLDisplay::~ZGLDisplay()
{
    if (_surface != NULL) {
        SDL_FreeSurface(_surface);
    }
}


#pragma mark - Initialization

void ZGLDisplay::initialize()
{
    if (!_isInitialized) {
        _loadSurface();
        _loadViewport();
        _loadCoordinateSystem();
        _changeWindowTitle(_displayMode.windowTitle);
        
        _initOpenGL();
        
        _isInitialized = true;
    } else {
        ZLogger::warn("Display already initialized.");
    }
}


#pragma mark - Rendering

void ZGLDisplay::render(unsigned dtime)
{    
    _lastRender += dtime;
    if (_lastRender >= _displayMode.refreshRate) {
        _lastRender = 0;
        SDL_GL_SwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}


#pragma mark - Changing Properties

void ZGLDisplay::setDisplayMode(const ZDisplayMode &mode)
{
    if (mode.windowTitle != _displayMode.windowTitle) {
        _changeWindowTitle(mode.windowTitle);
    }
    
    _displayMode = mode;
    
    if (_isInitialized) {
        _loadViewport();
    }
}

void ZGLDisplay::setCoordinateSystem(const ZCoordinateSystemf &coordSystem)
{
    _coordinateSystem = coordSystem;
    
    if (_isInitialized) {
        _loadCoordinateSystem();
    }
}


#pragma mark - Private Methods

void ZGLDisplay::_loadSurface()
{
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);     // Request 16-bit depth
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Request double-buffering
    
    Uint32 sdlFlags = SDL_OPENGL;
    if (!_displayMode.windowed) {
        sdlFlags |= SDL_FULLSCREEN;
    }
    
    if (_surface != NULL) {
        SDL_FreeSurface(_surface);
    }
    _surface = SDL_SetVideoMode(_displayMode.width, _displayMode.height, 0, sdlFlags);
    if (!_surface) {
        std::string errorStr = "The OpenGL display surface failed to initialize: ";
        errorStr += SDL_GetError();
        
        ZDisplayException expt;
        expt.description = errorStr;
        throw expt;
    }
}

void ZGLDisplay::_loadViewport()
{
    glViewport(0, 0, _displayMode.width, _displayMode.height);
}

void ZGLDisplay::_loadCoordinateSystem()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (_coordinateSystem.isZero()) {
        glOrtho(0, 1024, 0, 768, -512, 512);
    } else {
        glOrtho(0,
                _coordinateSystem.width,
                0,
                _coordinateSystem.height,
                -_coordinateSystem.depth,
                _coordinateSystem.depth);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void ZGLDisplay::_initOpenGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0f);
}

void ZGLDisplay::_changeWindowTitle(string newTitle)
{
    const char *windowTitle = newTitle.c_str();
    SDL_WM_SetCaption(windowTitle, windowTitle);
}

} // namespace zge