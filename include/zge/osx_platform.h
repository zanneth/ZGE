/*
 * osx_platform.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#pragma once

#include "zge/platform.h"
#include "zge/noncopyable.h"

#include <string>

namespace zge {

class ZApplication;

class ZOSXPlatform : public ZPlatform, ZNoncopyable {
public:
    void run_application(ZApplication *application) override;
    std::string get_description() override;

private:
    void _setup_main_menu();
};

} // namespace zge


@interface ZAppDelegate : NSObject <NSApplicationDelegate> {
    zge::ZApplication *_application;
}

@property (nonatomic, assign) zge::ZApplication *application;

@end
