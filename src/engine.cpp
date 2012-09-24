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
    static ZEngine engine;
    return &engine;
}

ZEngine::ZEngine() :
    _display_manager(new ZDisplayManager),
    _game_manager(new ZGameManager),
    _input_manager(new ZInputManager)
{}


#pragma mark - Initialization

void ZEngine::initialize()
{
    ZRunloop *loop = ZApplication::get_main_runloop();
    if (!loop) {
        ZEngineException e;
        e.extra_info = "Main run loop not available. Engine initialization failed.";
        throw e;
    }
    
    loop->schedule(_display_manager);
    loop->schedule(_game_manager);
    loop->schedule(_input_manager);
}

} // namespace zge
