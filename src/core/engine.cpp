/*
 * engine.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#include "zge/engine.h"
#include "zge/application.h"
#include "zge/exception.h"
#include "zge/run_loop.h"

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
        if (event.type == APPLICATION_EVENT) {
            ZApplication *app = ZApplication::get_current_application();
            if (app) {
                app->handle_application_event(event);
            }
        }
    });
    
    // push an "active" event through since SDL doesn't do it when the app launches
    ZEvent event;
    event.type = APPLICATION_EVENT;
    event.event.application_event = APPLICATION_ACTIVE_EVENT;
    _input_manager->push_event(event);
}

} // namespace zge
