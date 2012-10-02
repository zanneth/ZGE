/*
 * input_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include "zge/input_manager.h"
#include "zge/application.h"
#include "zge/run_loop.h"
#include <SDL/SDL.h>

namespace zge {

void ZInputManager::run(unsigned dtime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                ZRunloop *mainloop = ZApplication::get_main_runloop();
                mainloop->stop();
                break;
            }
            case SDL_KEYDOWN:
                // TODO
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
