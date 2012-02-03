//
//  display_manager.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/runnable_interface.h"
#include "zge/display.h"
#include <memory>

namespace zge {

typedef std::shared_ptr<class ZDisplayManager> ZDisplayManagerRef;

class ZDisplayManager : public ZRunnableInterface {
    ZDisplayRef _currentDisplay;
    
public:
    /** Accessors **/
    ZDisplayRef getCurrentDisplay() const { return _currentDisplay; }
    void setCurrentDisplay(ZDisplayRef display);
    
    
    /** Runnable **/
    void run(unsigned dtime) override;
};

} // namespace zge