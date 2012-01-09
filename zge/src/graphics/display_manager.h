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
using std::shared_ptr;

class ZDisplay;
class ZDisplayManager : public ZRunnableInterface {
    shared_ptr<ZDisplay> _currentDisplay;
    
public:
    /** Accessors **/
    shared_ptr<ZDisplay> getCurrentDisplay() const { return _currentDisplay; }
    void setCurrentDisplay(shared_ptr<ZDisplay> display);
    
    
    /** Runnable **/
    void update(unsigned dtime) override;
};

}

#endif // _ZGE_DISPLAY_MANAGER_H_
