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
    _displayManager(new ZDisplayManager),
    _gameManager(new ZGameManager),
    _inputManager(new ZInputManager)
{}


#pragma mark - Initialization

void ZEngine::initialize()
{
    ZRunLoop *mainLoop = ZApplication::getMainRunLoop();
    if (!mainLoop) {
        ZEngineException e;
        e.extraInfo = "Main run loop not available. Engine initialization failed.";
        throw e;
    }
    
    mainLoop->schedule(_displayManager);
    mainLoop->schedule(_gameManager);
    mainLoop->schedule(_inputManager);
}

} // namespace zge
