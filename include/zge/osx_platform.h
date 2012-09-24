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

class application;
class osx_platform : public platform, noncopyable {
public:
    void run_application(application *application) override;
    std::string get_description() override;

private:
    void _setup_main_menu();
};

} // namespace zge


@interface AppDelegate : NSObject <NSApplicationDelegate> {
    zge::application *_application;
}

@property (nonatomic, assign) zge::application *application;

@end
