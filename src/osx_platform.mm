/*
 * osx_platform.mm
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include "zge/osx_platform.h"
#include "zge/application.h"

#include <string>
#include <sstream>
#include <SDL/SDL.h>

namespace zge {

void ZOSXPlatform::runApplication(ZApplication *application)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    [NSApplication sharedApplication]; // Initialize the application if it hasn't been already
    
    // Create the App Delegate
    ZAppDelegate *appDelegate = [[ZAppDelegate alloc] init];
    appDelegate.application = application;
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

std::string ZOSXPlatform::getDescription()
{
    NSProcessInfo *pinfo = [NSProcessInfo processInfo];
    NSString *version = [pinfo operatingSystemVersionString];
    
    std::ostringstream oss;
    oss << "Mac OS X " << [version UTF8String];
    
    return oss.str();
}

void ZOSXPlatform::_setupMainMenu()
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
        _application->startMainRunLoop(); // does not return until engine exits
        [NSApp terminate:self];
    }
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

- (void)dealloc
{
    delete _application;
    [super dealloc];
}

@end
