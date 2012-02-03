//
//  osx_platform.h
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#pragma once

#include "zge/platform.h"

namespace zge {

class ZApplication;
class ZOSXPlatform : public ZPlatform {
public:
    void runApplication(ZApplication *application) override;

private:
    void _setupMainMenu();
};

} // namespace zge


using zge::ZApplication;

@interface ZAppDelegate : NSObject <NSApplicationDelegate> {
    ZApplication *application;
}

@property (nonatomic, assign) ZApplication *application;

@end