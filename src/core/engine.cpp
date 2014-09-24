/*
 * engine.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#include <zge/engine.h>
#include <zge/application.h>
#include <zge/display.h>
#include <zge/exception.h>
#include <zge/run_loop.h>

BEGIN_ZGE_NAMESPACE

ZEngine* ZEngine::instance()
{
    static ZEngine __engine;
    return &__engine;
}

ZEngine::ZEngine() :
    _input_manager(new ZInputManager),
    _render_manager(new ZRenderManager),
    _audio_manager(new ZAudioManager)
{}

#pragma mark - Initialization

void ZEngine::initialize()
{
    ZApplication *app = ZApplication::get_current_application();
    if (!app) {
        ZException e(ZENGINE_EXCEPTION_CODE);
        e.extra_info = "Main run loop not available. Engine initialization failed.";
        throw e;
    }
    
    ZRunloop *loop = app->get_main_runloop();
    loop->schedule(_input_manager);
    loop->schedule(_render_manager);
    loop->schedule(_audio_manager);
    
    // engine always adds application as the first responder
    _application_responder = _input_manager->add_responder([](const ZEvent &event) {
        if (event.type == ZAPPLICATION_EVENT) {
            ZApplication *app = ZApplication::get_current_application();
            if (app) {
                app->handle_application_event(event);
            }
        }
    });
}

#pragma mark - Accessors

ZInputManagerRef ZEngine::get_input_manager() { return _input_manager; }
ZRenderManagerRef ZEngine::get_render_manager() { return _render_manager; }
ZAudioManagerRef ZEngine::get_audio_manager() { return _audio_manager; }

#pragma mark - Utility

ZRect ZEngine::get_viewport_rect() const
{
    ZRect viewport_rect;
    ZDisplayRef cur_display = _render_manager->get_current_display();
    if (cur_display) {
        ZDisplayMode disp_mode = cur_display->get_display_mode();
        viewport_rect = {
            ZPoint2D(),
            { (float)disp_mode.width, (float)disp_mode.height }
        };
    }
    
    return viewport_rect;
}

ZSceneRef ZEngine::get_current_scene() const
{
    return _render_manager->get_scene();
}

void ZEngine::set_current_scene(ZSceneRef scene)
{
    _render_manager->set_scene(scene);
}

END_ZGE_NAMESPACE
