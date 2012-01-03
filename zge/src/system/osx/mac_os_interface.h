//
//  mac_os_interface.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#ifndef _ZGE_MAC_OS_INTERFACE_H_
#define _ZGE_MAC_OS_INTERFACE_H_

#include "base_os_interface.h"

namespace zge {

class ZBaseApplication;

class ZMacOSInterface : public ZBaseOSInterface {
public:
    void initialize();

private:
    void _setupMainMenu();
};

}

@interface ZAppDelegate : NSObject <NSApplicationDelegate> {
    zge::ZBaseApplication *application;
}

@property (nonatomic, assign) zge::ZBaseApplication *application;

@end

#endif
