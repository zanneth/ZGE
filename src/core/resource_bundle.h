/*
 * resource_bundle.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#pragma once

#include <zge/foundation.h>

BEGIN_ZGE_NAMESPACE

class ZResourceBundle : ZNoncopyable {
public:
    ZResourceBundle(std::string path);
    
    static ZResourceBundle* get_main_bundle();
    
    std::string get_bundle_path() const;
    std::string get_path_for_resource(std::string filename);
    std::string append_path_component(std::string path, std::string component);
    std::string append_path_components(std::string path, std::vector<std::string> components);
    
private:
    std::string _base_path;
    char        _path_separator;
};

END_ZGE_NAMESPACE
