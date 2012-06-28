/*
 * gl_display.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/gl_display.h"
#include "zge/gl_includes.h"
#include "zge/logger.h"
#include "zge/matrix.h"
#include "zge/util.h"
#include "zge/vector.h"

#include <iostream>
#include <string>

namespace zge {

ZGLDisplay::ZGLDisplay() : ZDisplay(),
    _surface(nullptr) {}

ZGLDisplay::ZGLDisplay(const ZDisplayMode &mode) : ZDisplay(mode),
    _surface(nullptr) {}

ZGLDisplay::~ZGLDisplay()
{
    if (_surface != nullptr) {
        SDL_FreeSurface(_surface);
    }
}


#pragma mark - Initialization

void ZGLDisplay::initialize()
{
    if (!_isInitialized) {
        _loadSurface();
        _loadViewport();
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
    if (_lastRender >= _displayMode.refreshRate * 1000.0) {
        _lastRender = 0;
        
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // TODO: Testing code below
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        float aspect = _displayMode.width / _displayMode.height;
        ZMatrix4 proj = ZMatrix4::perspective(45.0, aspect, 0.001, 10000.0);
        glMultMatrixf(proj.matrix);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        static float rot = 0.0;
        ZMatrix4 model = ZMatrix4::rotation((rot++), 1.0, 1.0, 1.0);
        model *= ZMatrix4::lookAt(ZVec3(0.0, 0.0, 5.0), ZVec3(), ZVec3(0.0, 1.0, 0.0));
        glMultMatrixf(model.matrix);
        glColor3f(1.0, 1.0, 1.0);
        glutWireCube(1.0);
        
        // END test code
        
        SDL_GL_SwapBuffers();
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
        expt.extraInfo = errorStr;
        throw expt;
    }
}

void ZGLDisplay::_loadViewport()
{
    glViewport(0, 0, _displayMode.width, _displayMode.height);
}

void ZGLDisplay::_initOpenGL()
{
    glEnable(GL_DEPTH_TEST);
}

void ZGLDisplay::_changeWindowTitle(std::string newTitle)
{
    const char *windowTitle = newTitle.c_str();
    SDL_WM_SetCaption(windowTitle, windowTitle);
}

} // namespace zge
