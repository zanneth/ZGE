//
//  game_manager.h
//  ZGE
//
//  Created by Charles Magahern on 1/9/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/runnable_interface.h"
#include <memory>

namespace zge {

typedef std::shared_ptr<class ZGameManager> ZGameManagerRef;

class ZGameManager : public ZRunnableInterface {
    
public:
    // TODO
};

} // namespace zge