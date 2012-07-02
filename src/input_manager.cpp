/*
 * input_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include "zge/input_manager.h"
#include <SDL/SDL.h>
#include <iostream>

namespace zge {

void ZInputManager::run(unsigned dtime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0); // FIXME: Temporary
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q) {
                    exit(0);
                }
                break;
            default:
                break;
        }
    }
}

} // namespace zge