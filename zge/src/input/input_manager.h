//
//  input_manager.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_INPUT_MANAGER_H_
#define _ZGE_INPUT_MANAGER_H_

#include <zge/interfaces/runnable_interface.h>

namespace zge {

class ZInputManager : public ZRunnableInterface {
public:    
    void run(unsigned dtime) override;
};

}

#endif // _ZGE_INPUT_MANAGER_H_
