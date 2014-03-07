/*
 * defines.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 03/06/2014
 */

#pragma once

#include <cstdint>
#include <iostream>

#define ZDEBUG 1

#define ZHEREDOC(...) std::string(#__VA_ARGS__)

#define BEGIN_ZGE_NAMESPACE namespace zge {
#define END_ZGE_NAMESPACE }

#define ZFORMATARG(FORMAT_ARG, VA_ARG) __attribute__((__format__(printf,FORMAT_ARG,VA_ARG)))
