/*
 * engine.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/application.h>
#include <zge/audio_manager.h>
#include <zge/input_manager.h>
#include <zge/noncopyable.h>
#include <zge/render_manager.h>
#include <zge/types.h>

ZGE_BEGIN_NAMESPACE

class ZEngine : ZNoncopyable {
public:
    ZEngine();
    ~ZEngine();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZEngine);
    
    /// Initialize the engine's internal state. Must provide a runloop on which
    /// to schedule updates.
    void initialize(ZRunloopRef runloop);
    
    /// Returns the application instance associated with this engine.
    ZApplication* get_application() const;
    
    /// Sets the application instance associated with this engine. The engine
    /// will send application-related events to this object, such as quit,
    /// become active, and resign active events. This is optional but
    /// recommended for optimal application behavior.
    void set_application(ZApplication *application);
    
    /// Returns the engine's input manager. The input manager handles all
    /// incoming input events and dispatches them to its event handlers.
    ZInputManagerRef get_input_manager();
    
    /// Returns the engine's render manager. The render manage is responsible
    /// for updating the display/window and rendering the scene object.
    ZRenderManagerRef get_render_manager();
    
    /// Returns the engine's audio manager. The audio manager plays sound
    /// objects that are sent to it through the add_sound() function.
    ZAudioManagerRef get_audio_manager();
    
    /// Returns the rectangle representing render manager's current display.
    ZRect get_viewport_rect() const;
    
    // Convenience: returns the render manager's current scene property.
    ZSceneRef get_current_scene() const;
    
    // Convenience: sets the render manager's current scene.
    void set_current_scene(ZSceneRef scene);
    
private:
    ZInputManagerRef  _input_manager;
    ZRenderManagerRef _render_manager;
    ZAudioManagerRef  _audio_manager;
    
    ZApplication     *_application;
    ZResponderRef     _application_responder;
};

ZGE_DEFINE_SREF_TYPE(ZEngine);

ZGE_END_NAMESPACE
