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

class engine : noncopyable {
    display_manager_ref  _display_manager;
    game_manager_ref     _game_manager;
    input_manager_ref    _input_manager;

public:
    static engine* instance();
    
    /** Accessors **/
    display_manager_ref get_display_manager() { return _display_manager; }
    game_manager_ref get_game_manager() { return _game_manager; }
    input_manager_ref get_input_manager() { return _input_manager; }
    
    /** Initialization **/
    void initialize();
    
private:
    // singleton
    engine();
};

} // namespace zge
