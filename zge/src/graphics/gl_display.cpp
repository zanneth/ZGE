//
//  gl_display.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "gl_display.h"

#include <iostream>
#include <string>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

#include <zge/util/logger.h>
#include <zge/util/util.h>


namespace zge {

ZGLDisplay::~ZGLDisplay()
{
    if (_surface != NULL) {
        SDL_FreeSurface(_surface);
        _surface = NULL;
    }
}


#pragma mark - Initialization

void ZGLDisplay::initialize()
{
    if (!_isInitialized) {
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);     // Request 16-bit depth
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Request double-buffering
        
        Uint32 sdlFlags = SDL_OPENGL;
        
        if (!_displayMode.windowed) {
            sdlFlags |= SDL_FULLSCREEN;
        }
        
        _surface = SDL_SetVideoMode(_displayMode.width, _displayMode.height, 0, sdlFlags);
        if (!_surface) {
            std::string errorStr = "The OpenGL display surface failed to initialize: ";
            errorStr += SDL_GetError();
            
            ZError err(ZGE_DISPLAY_INIT_ERROR, errorStr);
            util::fatalError(err);
        }
        
        const char *windowName = _displayMode.windowTitle.c_str();
        SDL_WM_SetCaption(windowName, windowName);
        
        _isInitialized = true;
        _reloadViewport();
        _reloadCoordinateSystem();
    } else {
        LOGGER->debugLog("Warning: Display already initialized.");
    }
}


#pragma mark - Rendering

void ZGLDisplay::render(unsigned dtime)
{    
    _lastRender += dtime;
    if (_lastRender >= _displayMode.refreshRate) {
        _lastRender = 0;
        SDL_GL_SwapBuffers();
    }
}


#pragma mark - Changing Properties

ZError ZGLDisplay::setDisplayMode(const ZDisplayMode &mode)
{
    if (mode.windowTitle != _displayMode.windowTitle) {
        const char *windowName = mode.windowTitle.c_str();
        SDL_WM_SetCaption(windowName, windowName);
    }
    
    _displayMode = mode;
    
    if (_isInitialized) {
        _reloadViewport();
    }
    
    return ZError::ZErrorNone();
}

ZError ZGLDisplay::setCoordinateSystem(const ZCoordinateSystem &coordSystem)
{
    if (_coordinateSystem != coordSystem) {
        _coordinateSystem = coordSystem;
        _reloadCoordinateSystem();
    }
        
    return ZError::ZErrorNone();
}


#pragma mark - Private Methods

void ZGLDisplay::_initOpenGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    _reloadViewport();
    _reloadCoordinateSystem();
}

void ZGLDisplay::_reloadViewport()
{
    glViewport(0, 0, _displayMode.width, _displayMode.height);
}

void ZGLDisplay::_reloadCoordinateSystem()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (_coordinateSystem == ZCoordinateSystemZero) {
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

}
