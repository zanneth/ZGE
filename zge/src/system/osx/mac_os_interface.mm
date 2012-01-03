//
//  mac_os_interface.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "mac_os_interface.h"
#include <SDL/SDL.h>

namespace zge {

void ZMacOSInterface::initialize()
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    [NSApplication sharedApplication]; // Initialize the application if it hasn't been already
    
    // Create the App Delegate
    ZAppDelegate *appDelegate = [[ZAppDelegate alloc] init];
    appDelegate.application = _application;
    [NSApp setDelegate:appDelegate];
    
    // Setup the Menu Bar
    NSMenu *mainMenu = [[[NSMenu alloc] init] autorelease];
    [NSApp setMainMenu:mainMenu];
    _setupMainMenu();
    
    // Start the Main Event Loop
    [NSApp run];
    
    [appDelegate release];
    [pool release];
}

void ZMacOSInterface::_setupMainMenu()
{
    NSString *appName = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"];
    NSMenu *appMenu = [[NSMenu alloc] init];
    
    NSMenuItem *menuItem;
    NSString *title;
    
    title = [NSString stringWithFormat:@"Hide %@", appName];
    [appMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];
    
    menuItem = [appMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask | NSCommandKeyMask)];
    
    [appMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
    
    [appMenu addItem:[NSMenuItem separatorItem]];
    
    title = [NSString stringWithFormat:@"Quit %@", appName];
    [appMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];
    
    /* Add Menu to Bar */
    menuItem = [[NSMenuItem alloc] init];
    [menuItem setSubmenu:appMenu];
    [[NSApp mainMenu] addItem:menuItem];
    
    [appMenu release];
}

}


@implementation ZAppDelegate
@synthesize application=_application;

- (void)_changeWorkingDirectory
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    
    char path[PATH_MAX];
    CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX);
    CFRelease(resourcesURL);
    
    chdir(path);
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    [self _changeWorkingDirectory];
    
    if (_application != NULL) {
        _application->applicationReady();
    }
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}

@end
