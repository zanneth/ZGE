//
//  display_manager.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/runnable_interface.h"
#include <memory>

namespace zge {
using std::shared_ptr;

class ZDisplay;
class ZDisplayManager : public ZRunnableInterface {
    shared_ptr<ZDisplay> _currentDisplay;
    
public:
    /** Accessors **/
    shared_ptr<ZDisplay> getCurrentDisplay() const { return _currentDisplay; }
    void setCurrentDisplay(shared_ptr<ZDisplay> display);
    
    
    /** Runnable **/
    void run(unsigned dtime) override;
};

} // namespace zge