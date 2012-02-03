//
//  input_manager.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/runnable_interface.h"
#include <memory>

namespace zge {

typedef std::shared_ptr<class ZInputManager> ZInputManagerRef;

class ZInputManager : public ZRunnableInterface {
public:    
    void run(unsigned dtime) override;
};

} // namespace zge