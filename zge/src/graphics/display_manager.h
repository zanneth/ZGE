//
//  display_manager.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_DISPLAY_MANAGER_H_
#define _ZGE_DISPLAY_MANAGER_H_

#include <memory>
#include <zge/interfaces/runnable_interface.h>


namespace zge {

class ZDisplay;

class ZDisplayManager : public ZRunnableInterface {
    std::auto_ptr<ZDisplay> _currentDisplay;
    
public:
    /** Accessors **/
    void setCurrentDisplay(ZDisplay *display) { _currentDisplay.reset(display); } // Claims ownership
    
    
    /** Runnable **/
    void update(unsigned dtime);
};

}

#endif // _ZGE_DISPLAY_MANAGER_H_
