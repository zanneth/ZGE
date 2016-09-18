/*
 * describable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/22/2014
 */

#pragma once

#include <zge/core/defines.h>
#include <string>
#include <vector>

ZGE_BEGIN_NAMESPACE

class ZDescribable {
public:
    virtual ~ZDescribable() = default;
    
    virtual std::string get_class_name() const;
    virtual std::vector<std::string> get_description_attributes() const;
    virtual std::string get_description() const;
};

ZGE_END_NAMESPACE
