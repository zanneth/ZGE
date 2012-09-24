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

engine* engine::instance()
{
    static engine engine;
    return &engine;
}

engine::engine() :
    _display_manager(new display_manager),
    _game_manager(new game_manager),
    _input_manager(new input_manager)
{}


#pragma mark - Initialization

void engine::initialize()
{
    runloop *loop = application::get_main_runloop();
    if (!loop) {
        engine_exception e;
        e.extra_info = "Main run loop not available. Engine initialization failed.";
        throw e;
    }
    
    loop->schedule(_display_manager);
    loop->schedule(_game_manager);
    loop->schedule(_input_manager);
}

} // namespace zge
