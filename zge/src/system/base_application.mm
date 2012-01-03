//
//  base_application.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "base_application.h"
#include "base_os_interface.h"
#include "mac_os_interface.h"

#include <iostream>

namespace zge {

ZBaseApplication::ZBaseApplication(int argc, char **argv)
{
    setArguments(argc, argv);
}


#pragma mark - Accessors

void ZBaseApplication::setArguments(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i) {
        std::string str = argv[i];
        _arguments.push_back(str);
    }
}


#pragma mark - Running the Application

void ZRunApplication(ZBaseApplication *application)
{
    if (application == NULL) {
        std::cerr << "FATAL ERROR: Application pointer is NULL." << std::endl;
        std::exit(1);
    }
    
    ZBaseOSInterface *interface;
#if __APPLE__
    interface = new ZMacOSInterface();
#endif
    
    interface->setApplication(application);
    interface->initialize();
}

}
