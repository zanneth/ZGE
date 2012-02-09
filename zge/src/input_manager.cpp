//
//  input_manager.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

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
                //exit(0); // FIXME: Temporary
                break;
            default:
                break;
        }
    }
}

} // namespace zge