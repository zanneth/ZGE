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

namespace zge {

ZEngine* ZEngine::instance()
{
    static ZEngine __engine;
    return &__engine;
}

ZEngine::ZEngine() :
    _display_manager(new ZDisplayManager),
    _game_manager(new ZGameManager),
    _input_manager(new ZInputManager)
{}

#pragma mark - Initialization

void ZEngine::initialize()
{
    ZApplication *app = ZApplication::get_current_application();
    if (!app) {
        ZException e(ENGINE_EXCEPTION_CODE);
        e.extra_info = "Main run loop not available. Engine initialization failed.";
        throw e;
    }
    
    ZRunloop *loop = app->get_main_runloop();
    loop->schedule(_display_manager);
    loop->schedule(_game_manager);
    loop->schedule(_input_manager);
    
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

#pragma mark - Utility

ZRect ZEngine::get_viewport_rect() const
{
    ZRect viewport_rect;
    ZDisplay *cur_display = _display_manager->get_current_display();
    if (cur_display != nullptr) {
        ZDisplayMode disp_mode = cur_display->get_display_mode();
        ZVec2 min(0.f, 0.f);
        ZVec2 max(disp_mode.width, disp_mode.height);
        viewport_rect = ZRect(min, max);
    }
    
    return viewport_rect;
}

} // namespace zge
