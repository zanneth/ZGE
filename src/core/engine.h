/*
 * engine.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include "zge/display_manager.h"
#include "zge/game_manager.h"
#include "zge/input_manager.h"

namespace zge {

class ZEngine : ZNoncopyable {
    ZDisplayManagerRef  _display_manager;
    ZGameManagerRef     _game_manager;
    ZInputManagerRef    _input_manager;
    
    ZResponderRef       _application_responder;

public:
    static ZEngine* instance();
    
    /** Accessors **/
    ZDisplayManagerRef get_display_manager() { return _display_manager; }
    ZGameManagerRef get_game_manager() { return _game_manager; }
    ZInputManagerRef get_input_manager() { return _input_manager; }
    
    /** Initialization **/
    void initialize();
    
private:
    // singleton
    ZEngine();
};

} // namespace zge
