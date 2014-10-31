/*
 * describable.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/22/2014
 */

#include "describable.h"
#include <sstream>
#include <typeinfo>

ZGE_BEGIN_NAMESPACE

std::string ZDescribable::get_class_name() const
{
    return typeid(*this).name();
}

std::vector<std::string> ZDescribable::get_description_attributes() const
{
    return {};
}

std::string ZDescribable::get_description() const
{
    std::ostringstream stream;
    stream << '<' << get_class_name() << ' ' << std::hex << this;
    
    std::vector<std::string> attrlist = get_description_attributes();
    for (const std::string &attr : attrlist) {
        stream << ' ' << attr;
    }
    
    stream << '>';
    return stream.str();
}

ZGE_END_NAMESPACE
