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

class ZEngine : ZNonCopyable {
    ZDisplayManagerRef  _displayManager;
    ZGameManagerRef     _gameManager;
    ZInputManagerRef    _inputManager;

public:
    static ZEngine* instance();
    
    /** Accessors **/
    ZDisplayManagerRef getDisplayManager() { return _displayManager; }
    ZGameManagerRef getGameManager() { return _gameManager; }
    ZInputManagerRef getInputManager() { return _inputManager; }
    
    /** Initialization **/
    void initialize();
    
private:
    // singleton
    ZEngine();
};

} // namespace zge
