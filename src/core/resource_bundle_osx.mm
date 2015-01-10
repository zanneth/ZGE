/*
 * resource_bundle_osx.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/10/2015
 */

#include <zge/resource_bundle.h>
#include <Eigen/Core> // must include Eigen headers first as this conflicts with ObjC runtime headers
#include <Foundation/Foundation.h>

ZGE_BEGIN_NAMESPACE

ZResourceBundle* ZResourceBundle::get_library_bundle()
{
    NSBundle *frmwk_bundle = [NSBundle bundleWithIdentifier:@"com.zanneth.ZGE"];
    std::string base_path = [[frmwk_bundle resourcePath] UTF8String];
    
    static ZResourceBundle library_bundle(base_path);
    library_bundle._path_separator = '/';
    return &library_bundle;
}

ZGE_END_NAMESPACE
