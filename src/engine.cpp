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
{
    // engine always adds itself as the first responder
    _engine_responder = _input_manager->add_responder([this](const ZEvent &event) {
        if (event.type == APPLICATION_EVENT) {
            this->_handle_application_event(event.event.application_event);
        }
    });
}

#pragma mark - Initialization

void ZEngine::initialize()
{
    ZRunloop *loop = ZApplication::get_main_runloop();
    if (!loop) {
        ZException e(ENGINE_EXCEPTION_CODE);
        e.extra_info = "Main run loop not available. Engine initialization failed.";
        throw e;
    }
    
    loop->schedule(_display_manager);
    loop->schedule(_game_manager);
    loop->schedule(_input_manager);
}

#pragma mark - Internal

void ZEngine::_handle_application_event(ZApplicationEvent event)
{
    switch (event) {
        case APPLICATION_QUIT_EVENT: {
            ZRunloop *main_loop = ZApplication::get_main_runloop();
            main_loop->stop();
            break;
        }
        default:
            break;
    }
}

} // namespace zge
