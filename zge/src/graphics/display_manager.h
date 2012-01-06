//
//  display_manager.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_DISPLAY_MANAGER_H_
#define _ZGE_DISPLAY_MANAGER_H_

#include <boost/shared_ptr.hpp>
#include <zge/interfaces/runnable_interface.h>


namespace zge {

class ZDisplay;

class ZDisplayManager : public ZRunnableInterface {
    boost::shared_ptr<ZDisplay> _currentDisplay;
    
public:
    /** Accessors **/
    void setCurrentDisplay(boost::shared_ptr<ZDisplay> display)
        { _currentDisplay = display; }
    
    
    /** Runnable **/
    void update(unsigned dtime);
};

}

#endif // _ZGE_DISPLAY_MANAGER_H_
