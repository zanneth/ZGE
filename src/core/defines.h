/*
 * defines.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/06/2014
 */

#pragma once

#include <cstdint>
#include <iostream>

#define ZGE_DEBUG 1

#define ZGE_HEREDOC(...) std::string(#__VA_ARGS__)

#define ZGE_BEGIN_NAMESPACE namespace zge {
#define ZGE_END_NAMESPACE }

#define ZGE_FORMATARG(FORMAT_ARG, VA_ARG) __attribute__((__format__(printf,FORMAT_ARG,VA_ARG)))

#define ZGE_DEFINE_SREF_FUNCTIONS(CLASSNAME) \
    template<typename ... Args> \
    static std::shared_ptr<CLASSNAME> create(Args&& ... args) \
    { \
        return std::make_shared<CLASSNAME>(std::forward<Args>(args)...); \
    }

#define ZGE_DEFINE_SREF_TYPE(CLASSNAME) \
    typedef std::shared_ptr<CLASSNAME> CLASSNAME##Ref; \
    typedef std::shared_ptr<const CLASSNAME> CLASSNAME##ConstRef;

#define ZGE_FORWARD_DECLARE_SREF(CLASSNAME)						\
    class CLASSNAME;											\
    using CLASSNAME##Ref = std::shared_ptr<CLASSNAME>;			\
    using CLASSNAME##ConstRef = std::shared_ptr<const CLASSNAME>

