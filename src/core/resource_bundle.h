/*
 * resource_bundle.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#pragma once

#include <zge/foundation.h>

ZGE_BEGIN_NAMESPACE

class ZResourceBundle : ZNoncopyable {
public:
    ZResourceBundle(std::string path);
    
    static ZResourceBundle* get_main_bundle();
    static ZResourceBundle* get_library_bundle();
    
    std::string get_bundle_path() const;
    void set_bundle_path(const std::string &path);
    
    std::string get_path_for_resource(std::string filename);
    std::string append_path_component(std::string path, std::string component);
    std::string append_path_components(std::string path, std::vector<std::string> components);
    std::string get_basename(std::string path);
    std::string get_dirname(std::string path);
    
private:
    std::string _base_path;
    char        _path_separator;
};

ZGE_END_NAMESPACE
