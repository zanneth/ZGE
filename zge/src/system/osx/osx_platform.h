//
//  osx_platform.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#ifndef _ZGE_OSX_PLATFORM_H_
#define _ZGE_OSX_PLATFORM_H_

#include <zge/system/platform.h>

namespace zge {

class ZApplication;
class ZOSXPlatform : public ZPlatform {
public:
    void initialize() override;

private:
    void _setupMainMenu();
};

}


using zge::ZApplication;

@interface ZAppDelegate : NSObject <NSApplicationDelegate> {
    ZApplication *application;
}

@property (nonatomic, assign) ZApplication *application;

@end

#endif // _ZGE_OSX_PLATFORM_H_
