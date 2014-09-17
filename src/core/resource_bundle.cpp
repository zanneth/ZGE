/*
 * resource_bundle.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#include <zge/resource_bundle.h>
#include <zge/util.h>
#include <SDL2/SDL.h>

BEGIN_ZGE_NAMESPACE

static std::string _get_main_bundle_path(char *out_path_separator);

ZResourceBundle::ZResourceBundle(std::string path) :
    _base_path(path)
{}

#pragma mark -

ZResourceBundle* ZResourceBundle::get_main_bundle()
{
    char path_separator = '\0';
    std::string main_bundle_path = _get_main_bundle_path(&path_separator);
    
    static ZResourceBundle __main_bundle(main_bundle_path);
    __main_bundle._path_separator = path_separator;
    return &__main_bundle;
}

std::string ZResourceBundle::get_bundle_path() const
{
    return _base_path;
}

std::string ZResourceBundle::get_path_for_resource(std::string filename)
{
    return append_path_component(_base_path, filename);
}

std::string ZResourceBundle::append_path_component(std::string path, std::string component)
{
    std::string result;
    size_t len = path.size();
    
    if (len > 0 && path.back() == _path_separator) {
        result = path + component;
    } else {
        result = path + _path_separator + component;
    }
    
    return result;
}

std::string ZResourceBundle::append_path_components(std::string path, std::vector<std::string> components)
{
    for (std::string component : components) {
        if (path.back() != _path_separator) {
            path += _path_separator + component;
        } else {
            path += component;
        }
    }
    return path;
}

#pragma mark - Internal

std::string _get_main_bundle_path(char *out_path_separator)
{
    char *base_path = SDL_GetBasePath();
    size_t path_len = strlen(base_path);
    
    if (path_len > 2 && out_path_separator != nullptr) {
        *out_path_separator = base_path[path_len - 1];
    }
    
    std::string main_bundle_path(base_path);
    free(base_path);
    
    return main_bundle_path;
}

END_ZGE_NAMESPACE
